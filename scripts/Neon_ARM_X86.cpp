// 一般来说 neon是常在ARM 架构下进行数据的加速 为了在windows下验证结果，这里使用simde库，能够在x86下使用
// 安装库

// *************************************************************************************************************
// 输入：模型的输出是float32的的argmax的实现
#define SIMDE_ENABLE_NATIVE_ALIASES
#include "D:\SDKs\third_party\simde/arm/neon.h"  // 或 sse4.1.h, avx2.h 等  安装路径
void argmax_float32(const float* input, int H, int W, cv::Mat& output) {
	const int HW = H * W;
	const float* ch0 = input;          // channel 0
	const float* ch1 = input + HW;     // channel 1
	uint8_t* out = output.ptr<uint8_t>();

	const int simd_width = 4;
	const int aligned_len = (HW / simd_width) * simd_width;

	for (int i = 0; i < aligned_len; i += simd_width) {
		float32x4_t v0 = vld1q_f32(&ch0[i]);
		float32x4_t v1 = vld1q_f32(&ch1[i]);

		// 比较 v1 > v0 → 若 true，则结果为 1；否则为 0
		uint32x4_t cmp = vcgtq_f32(v1, v0);           // 0xFFFFFFFF or 0x00000000
		uint32x4_t res = vshrq_n_u32(cmp, 31);        // → 1 or 0

		// 转为 uint8_t 并存储
		uint16x4_t tmp16 = vmovn_u32(res);
		uint8x8_t tmp8 = vmovn_u16(vcombine_u16(tmp16, tmp16));
		vst1_u8(&out[i], tmp8);
	}

	// 处理尾部未对齐部分
	for (int i = aligned_len; i < HW; ++i) {
		out[i] = (ch1[i] > ch0[i]) ? 1 : 0;
	}
}

// *************************************************************************************************************
// argmax的纯C++的实现
int HW = H * W;
for (int y = 0; y < H; ++y)
{
    for (int x = 0; x < W; ++x)
    {
        int idx = y * W + x;
        float v0 = instance_pred[0 * HW + idx];  
        float v1 = instance_pred[1 * HW + idx];
        instance_map.at<uint8_t>(y, x) = (v1 > v0) ? 1 : 0;
    }
}


// *************************************************************************************************************
// 这是将模型推理，模型输出是float32的，变成int8的输出的C++代码
std::vector<std::vector<Point>> FastScnn::predict(const cv::Mat& image, cv::Mat& half_mat, std::vector<signed char>& int8_mat, Point vp)
{
	int original_image_height = image.rows * 2 / 3;
	int original_image_width = image.cols;
	std::vector<std::vector<Point>> filter_nested_points;

#ifndef ARM_COMPLIE
	cv::Mat input;
	preprocess(image, input);
	std::vector<Ort::Value> ort_outputs;
	obj->run({ input }, ort_outputs);

	const auto info = ort_outputs[0].GetTensorTypeAndShapeInfo();
	size_t numel = info.GetElementCount();
	auto shape = info.GetShape();
	auto element_type = info.GetElementType();


	int num_classes = static_cast<int>(shape[1]); // num_classes
	int H = static_cast<int>(shape[2]);
	int W = static_cast<int>(shape[3]);
	int total_size = H * W * num_classes;

	float* data = (float*)ort_outputs[0].GetTensorData<float*>();
	// * ----->local use start float32->int8
	cv::Mat float_mat(num_classes, H * W, CV_32F, data);
	cv::transpose(float_mat, float_mat);

	// float_mat: (H*W, 2), CV_32F
	cv::Mat float_mat_flat = float_mat.reshape(1, 1); 
	double min_val, max_val;
	cv::minMaxLoc(float_mat_flat, &min_val, &max_val);


	float data_range = static_cast<float>(max_val - min_val);
	if (data_range < EPS_F32) data_range = 1.0f; 

	float scale = 127.0f / (data_range / 2.0f); 
	float center = static_cast<float>((max_val + min_val) / 2.0);

	std::vector<signed char> instance_pred(H * W * 2);
	for (int i = 0; i < H * W; ++i) {
		float ch0 = float_mat.at<float>(i, 0);
		float ch1 = float_mat.at<float>(i, 1);

		signed char c0 = static_cast<signed char>(
			std::round(std::max(-127.0f, std::min(127.0f, (ch0 - center) * scale)))
			);
		signed char c1 = static_cast<signed char>(
			std::round(std::max(-127.0f, std::min(127.0f, (ch1 - center) * scale)))
			);

		instance_pred[i * 2 + 0] = c0;
		instance_pred[i * 2 + 1] = c1;
	}
	int8_mat = instance_pred;
}

