# 1. 配置国内镜像加速
npm config set registry https://registry.npmmirror.com
 
# 2. 全局安装CLI
npm install -g @iflow-ai/iflow-cli
 
# 3. 启动配置向导


# LeetCode C++ 数据结构学习路线

## 学习顺序建议

### 阶段一：基础线性结构（入门必学，90%题目都会用到）
> 难度：⭐ | 重要性：⭐⭐⭐⭐⭐ | 熟练度要求：精通

1. **数组**
2. **字符串**
3. **链表**

### 阶段二：线性高级结构（中等难度，70%题目）
> 难度：⭐⭐ | 重要性：⭐⭐⭐⭐⭐ | 熟练度要求：熟练

4. **栈**
5. **队列**
6. **哈希表**

### 阶段三：树形结构（中等偏难，50%题目）
> 难度：⭐⭐⭐ | 重要性：⭐⭐⭐⭐⭐ | 熟练度要求：熟练

7. **二叉树**
8. **二叉搜索树（BST）**
9. **堆（优先队列）**

### 阶段四：图结构（中等偏难，30%题目）
> 难度：⭐⭐⭐ | 重要性：⭐⭐⭐⭐ | 熟练度要求：熟悉

10. **图**
11. **并查集**

### 阶段五：高级树结构（高级，15%题目）
> 难度：⭐⭐⭐⭐ | 重要性：⭐⭐⭐ | 熟练度要求：了解

12. **前缀树（Trie）**
13. **线段树**
14. **树状数组（Fenwick Tree）**

### 阶段六：特殊结构（特定问题，10%题目）
> 难度：⭐⭐⭐⭐⭐ | 重要性：⭐⭐ | 熟练度要求：了解

15. **单调栈**
16. **单调队列**
17. **红黑树/AVL树**（C++ STL已封装）

---

## 详细说明

### 一、数组

**C++ 实现：**
```cpp
// 静态数组
int arr[10];

// 动态数组（vector）
#include <vector>
vector<int> v;
v.push_back(1);
v.pop_back();
v.size();
v.empty();
```

**关键操作：**
- 遍历：O(n)
- 访问：O(1)
- 插入/删除（末尾）：O(1)
- 插入/删除（中间）：O(n)
- 查找：O(n)

**常见题型：**
- 双指针（Two Pointers）
- 滑动窗口
- 前缀和
- 排序相关问题

---

### 二、字符串

**C++ 实现：**
```cpp
#include <string>
string s = "hello";
s.substr(0, 3);
s.find("ll");
s.length();
```

**关键操作：**
- 拼接、分割
- 子串查找
- 字符串匹配（KMP算法）

**常见题型：**
- 字符串反转
- 最长回文子串
- 字符串匹配

---

### 三、链表

**C++ 实现：**
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

**关键操作：**
- 遍历：O(n)
- 插入/删除：O(1)（已知位置）
- 查找：O(n)

**常见题型：**
- 反转链表
- 快慢指针
- 合并链表
- 环形链表

---

### 四、栈

**C++ 实现：**
```cpp
#include <stack>
stack<int> s;
s.push(1);
s.pop();
s.top();
s.empty();
```

**关键操作：**
- 压栈、弹栈：O(1)
- 查看栈顶：O(1)

**常见题型：**
- 括号匹配
- 逆波兰表达式
- 单调栈

---

### 五、队列

**C++ 实现：**
```cpp
#include <queue>
queue<int> q;
q.push(1);
q.pop();
q.front();
q.empty();
```

**关键操作：**
- 入队、出队：O(1)
- 查看队首：O(1)

**常见题型：**
- 层序遍历
- BFS
- 滑动窗口最大值

---

### 六、哈希表

**C++ 实现：**
```cpp
#include <unordered_map>
#include <unordered_set>

unordered_map<int, int> mp;
mp[1] = 100;
mp.count(1);

unordered_set<int> st;
st.insert(1);
st.count(1);
```

**关键操作：**
- 插入、删除、查找：O(1) 平均

**常见题型：**
- 两数之和
- 字母异位词
- 最长连续序列

---

### 七、二叉树

**C++ 实现：**
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

**关键操作：**
- 遍历：前序、中序、后序、层序
- 递归深度：O(n)

**常见题型：**
- 二叉树遍历
- 二叉树的最大深度
- 最近公共祖先

---

### 八、二叉搜索树（BST）

**特性：**
- 左子树 < 根节点 < 右子树
- 中序遍历是有序的

**常见题型：**
- 验证BST
- 在BST中搜索
- 将有序数组转换为BST

---

### 九、堆（优先队列）

**C++ 实现：**
```cpp
#include <queue>
// 最大堆（默认）
priority_queue<int> max_heap;
// 最小堆
priority_queue<int, vector<int>, greater<int>> min_heap;

max_heap.push(1);
max_heap.pop();
max_heap.top();
```

**关键操作：**
- 插入、删除：O(log n)
- 查看堆顶：O(1)

**常见题型：**
- Top K 问题
- 堆排序
- 合并K个有序链表

---

### 十、图

**C++ 实现：**
```cpp
// 邻接矩阵
vector<vector<int>> graph(n, vector<int>(n));

// 邻接表
vector<vector<int>> adj(n);
adj[0].push_back(1);
```

**关键算法：**
- DFS（深度优先搜索）
- BFS（广度优先搜索）
- 最短路径（Dijkstra）
- 最小生成树（Kruskal/Prim）

**常见题型：**
- 岛屿数量
- 课程表（拓扑排序）
- 网络延迟时间

---

### 十一、并查集

**C++ 实现：**
```cpp
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unionSet(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }
    }
};
```

**常见题型：**
- 冗余连接
- 岛屿数量
- 省份数量

---

### 十二、前缀树（Trie）

**C++ 实现：**
```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEnd = false;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }
};
```

**常见题型：**
- 实现Trie
- 单词搜索
- 单词替换

---

### 十三、线段树

**用途：** 区间查询、区间修改

**常见题型：**
- 区间和查询
- 区间最大值查询
- 数组修改

---

### 十四、树状数组（Fenwick Tree）

**用途：** 单点修改、区间查询

**C++ 实现：**
```cpp
class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    
    void update(int i, int delta) {
        while (i <= n) {
            tree[i] += delta;
            i += i & (-i);
        }
    }
    
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }
};
```

**常见题型：**
- 区间和查询
- 逆序对数量

---

### 十五、单调栈

**用途：** 寻找下一个更大/更小元素

**常见题型：**
- 下一个更大元素
- 每日温度
- 柱状图中最大的矩形

---

### 十六、单调队列

**用途：** 滑动窗口最值

**常见题型：**
- 滑动窗口最大值
- 滑动窗口最小值

---

## 学习建议

### 必须掌握（前9种）
这些数据结构覆盖了 LeetCode 80% 以上的题目：
1. 数组 - 基础中的基础
2. 字符串 - 处理文本问题
3. 链表 - 指针操作
4. 栈 - 后进先出
5. 队列 - 先进先出
6. 哈希表 - 快速查找
7. 二叉树 - 递归思维
8. BST - 搜索树特性
9. 堆 - 优先级处理

### 进阶掌握（10-14种）
这些数据结构用于解决特定类型的中等偏难题目：
10. 图 - 复杂关系
11. 并查集 - 连通性问题
12. 前缀树 - 字符串前缀
13. 线段树 - 区间操作
14. 树状数组 - 区间操作

### 了解即可（15-17种）
这些结构通常有替代方案，或在特定场景下使用：
15. 单调栈 - 可用双指针替代
16. 单调队列 - 可用堆替代
17. 红黑树/AVL - STL已封装

---

## C++ STL 常用容器速查

| 容器 | 头文件 | 用途 |
|------|--------|------|
| vector | `<vector>` | 动态数组 |
| string | `<string>` | 字符串 |
| list | `<list>` | 双向链表 |
| deque | `<deque>` | 双端队列 |
| stack | `<stack>` | 栈 |
| queue | `<queue>` | 队列 |
| priority_queue | `<queue>` | 优先队列 |
| unordered_map | `<unordered_map>` | 哈希表 |
| unordered_set | `<unordered_set>` | 哈希集合 |
| map | `<map>` | 红黑树（有序） |
| set | `<set>` | 红黑树集合（有序） |

---

## 刷题策略

1. **按难度递进**：先刷 Easy，再刷 Medium，最后 Hard
2. **按主题练习**：同一个数据结构刷5-10题
3. **重视重复**：经典题目反复练习
4. **总结模板**：为每种数据结构准备代码模板
5. **时间限制**：每题控制在30分钟内

## 推荐刷题顺序

1. 数组（50题）
2. 字符串（30题）
3. 哈希表（30题）
4. 双指针（20题）
5. 滑动窗口（20题）
6. 链表（30题）
7. 栈和队列（30题）
8. 二叉树（40题）
9. 递归和回溯（30题）
10. 动态规划（50题）
11. 图（30题）
12. 堆（20题）
13. 高级数据结构（20题）

祝刷题顺利！