# LeetCode 哈希表详解：unordered_map 和 unordered_set

## 一、哈希表概述

哈希表（Hash Table）是一种基于键值对（Key-Value）存储的数据结构，通过哈希函数将键映射到存储位置，实现快速查找、插入和删除操作。

### 时间复杂度
- 平均情况：O(1)
- 最坏情况：O(n)（哈希冲突严重时）

### C++ STL 中的哈希表
C++ STL 提供了两种主要的哈希表容器：
1. **unordered_map** - 哈希映射（键值对）
2. **unordered_set** - 哈希集合（仅存储键）

---

## 二、unordered_map vs unordered_set 的区别

| 特性 | unordered_map | unordered_set |
|------|---------------|---------------|
| **存储内容** | 键值对（Key-Value） | 仅键（Key） |
| **用途** | 存储映射关系 | 存储唯一元素 |
| **访问方式** | 通过键访问值 | 只能查询键是否存在 |
| **键的唯一性** | 键唯一，值可重复 | 所有元素唯一 |
| **典型场景** | 两数之和、字符计数、映射关系 | 去重、判断存在性、集合运算 |
| **迭代器** | 指向 `pair<key, value>` | 指向 `key` |

---

## 三、unordered_map 详细用法

### 1. 头文件与定义

```cpp
#include <unordered_map>
using namespace std;

// 基本定义
unordered_map<int, int> mp;

// 指定初始大小
unordered_map<int, int> mp(100);

// 自定义哈希函数（针对复杂类型）
struct MyHash {
    size_t operator()(const vector<int>& v) const {
        size_t hash = 0;
        for (int x : v) {
            hash ^= hash * 31 + x;
        }
        return hash;
    }
};
unordered_map<vector<int>, int, MyHash> mp2;
```

### 2. 初始化与赋值

```cpp
// 方式1：逐个插入
unordered_map<int, string> mp;
mp[1] = "one";
mp[2] = "two";
mp[3] = "three";

// 方式2：初始化列表
unordered_map<int, string> mp2 = {
    {1, "one"},
    {2, "two"},
    {3, "three"}
};

// 方式3：复制构造
unordered_map<int, string> mp3(mp);

// 方式4：插入函数
unordered_map<int, string> mp4;
mp4.insert({4, "four"});
mp4.insert(make_pair(5, "five"));
mp4.insert(pair<int, string>(6, "six"));
```

### 3. 访问元素

```cpp
unordered_map<int, string> mp = {{1, "one"}, {2, "two"}};

// 方式1：下标访问（会自动创建默认值）
string val1 = mp[1];      // "one"
string val2 = mp[99];     // 自动创建 key=99，value=""（string默认值）

// 方式2：at() 方法（带边界检查）
string val3 = mp.at(1);   // "one"
// string val4 = mp.at(99); // 抛出 out_of_range 异常

// 方式3：find() 查找
auto it = mp.find(1);
if (it != mp.end()) {
    cout << it->first << ": " << it->second << endl;
}

// 方式4：count() 判断是否存在
if (mp.count(1)) {
    cout << "Key 1 exists" << endl;
}
```

### 4. 添加与更新元素

```cpp
unordered_map<int, string> mp;

// 方式1：下标赋值（覆盖已有值）
mp[1] = "one";
mp[1] = "ONE";  // 更新

// 方式2：insert()（不覆盖已有值）
mp.insert({2, "two"});
mp.insert({2, "TWO"});  // 失败，key=2 已存在

// 方式3：insert_or_assign()（C++17，覆盖已有值）
mp.insert_or_assign(3, "three");
mp.insert_or_assign(3, "THREE");  // 更新

// 方式4：emplace()（原地构造，更高效）
mp.emplace(4, "four");

// 方式5：try_emplace()（C++17，仅当键不存在时插入）
mp.try_emplace(5, "five");
mp.try_emplace(5, "FIVE");  // 失败，key=5 已存在
```

### 5. 删除元素

```cpp
unordered_map<int, string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

// 方式1：删除指定键
mp.erase(1);

// 方式2：通过迭代器删除
auto it = mp.find(2);
if (it != mp.end()) {
    mp.erase(it);
}

// 方式3：删除范围
mp.erase(mp.begin(), mp.end());  // 清空所有元素

// 方式4：条件删除
for (auto it = mp.begin(); it != mp.end(); ) {
    if (it->second.length() > 5) {
        it = mp.erase(it);  // 返回下一个有效迭代器
    } else {
        ++it;
    }
}
```

### 6. 常用操作

```cpp
unordered_map<int, string> mp = {{1, "one"}, {2, "two"}};

// 大小
int size = mp.size();       // 元素个数
bool empty = mp.empty();    // 是否为空

// 清空
mp.clear();

// 交换两个 map
unordered_map<int, string> mp2;
mp.swap(mp2);

// 获取迭代器
auto begin = mp.begin();    // 第一个元素
auto end = mp.end();        // 最后一个元素的下一个位置
auto cbegin = mp.cbegin();  // const 迭代器

// 预留空间（减少重新哈希）
mp.reserve(100);
```

### 7. 遍历

```cpp
unordered_map<int, string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

// 方式1：范围 for 循环（推荐）
for (const auto& [key, value] : mp) {  // C++17 结构化绑定
    cout << key << ": " << value << endl;
}

// 方式2：范围 for 循环（C++11）
for (const auto& p : mp) {
    cout << p.first << ": " << p.second << endl;
}

// 方式3：迭代器遍历
for (auto it = mp.begin(); it != mp.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
}

// 方式4：只遍历键
for (const auto& p : mp) {
    cout << p.first << endl;
}

// 方式5：只遍历值
for (const auto& p : mp) {
    cout << p.second << endl;
}
```

### 8. 查找操作

```cpp
unordered_map<int, string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

// 查找键
auto it = mp.find(2);
if (it != mp.end()) {
    cout << "Found: " << it->second << endl;
}

// 判断键是否存在
bool exists = mp.count(2);  // 返回 0 或 1

// 查找多个键
vector<int> keys = {1, 2, 3, 4, 5};
for (int key : keys) {
    if (mp.count(key)) {
        cout << key << " exists" << endl;
    }
}
```

### 9. 迭代器详解

#### 什么是迭代器？

**迭代器**是一个**智能指针**，用于遍历容器中的元素。它像指针一样可以指向容器中的某个元素，并支持移动到下一个元素。

```cpp
unordered_map<int, int> cnt = {{2, 0}, {7, 1}, {11, 2}};
auto it = cnt.find(7);  // find() 返回一个迭代器
```

这里的 `it` 是一个**指向 map 中某个元素的迭代器**。

#### 迭代器的本质

可以把迭代器理解为：
- 一个**位置标记**，指向容器中的某个元素
- 类似于数组的下标，但更通用

```cpp
// 数组方式理解：
// nums[0] = 2
// nums[1] = 7
// nums[2] = 11

// 迭代器方式理解：
// it 指向 {7, 1} 这个键值对
```

#### it->first 和 it->second 的含义

在 `unordered_map` 的迭代器中：

| 表达式 | 含义 | 示例值 |
|--------|------|--------|
| `it->first` | 键 | `7`（数字） |
| `it->second` | 值 | `1`（索引） |

#### 迭代器的常见操作

```cpp
unordered_map<int, int> cnt = {{2, 0}, {7, 1}, {11, 2}};
auto it = cnt.begin();  // 获取第一个元素的迭代器

// 访问元素
it->first;    // 键：2
it->second;   // 值：0

// 移动迭代器
++it;         // 移动到下一个元素
--it;         // 移动到上一个元素

// 比较
if (it != cnt.end()) {  // 判断是否有效
    // ...
}
```

#### find() 返回什么？

```cpp
auto it = cnt.find(b);
```

- **找到元素**：返回指向该元素的迭代器
- **未找到元素**：返回 `cnt.end()`（一个特殊的迭代器，表示"无效位置"）

```cpp
if (it != cnt.end()) {
    // 找到了！it 指向该元素
    // 可以访问 it->first 和 it->second
} else {
    // 没找到
}
```

#### 图解理解

```
unordered_map<int, int> cnt = {{2, 0}, {7, 1}, {11, 2}}

内存布局（概念性）：

容器：    [ {2, 0} ] → [ {7, 1} ] → [ {11, 2} ]
                              ↑
                              |
                             it

it 指向 {7, 1} 这个键值对
it->first = 7   （键）
it->second = 1  （值）
```

#### 迭代器 vs 普通指针

| 特性 | 迭代器 | 普通指针 |
|------|--------|----------|
| **指向** | 容器元素 | 内存地址 |
| **移动** | `++it`, `--it` | `++p`, `--p` |
| **访问** | `it->first`, `it->second` | `*p`, `p->field` |
| **适用** | STL容器（map, set, vector等） | 数组 |
| **安全性** | 有边界检查机制 | 容易越界 |

#### 实际例子：两数之和

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> cnt;  // 存储 {数字: 索引}
    
    for (int i = 0; i < nums.size(); i++) {
        int b = target - nums[i];  // 需要找的补数
        auto it = cnt.find(b);     // 查找补数
        
        if (it != cnt.end()) {
            // 找到了！
            // it->first 是补数 b
            // it->second 是补数的索引
            return {it->second, i};  // 返回 {补数的索引, 当前索引}
        }
        else {
            cnt[nums[i]] = i;  // 存储当前数字及其索引
        }
    }
    return {};
}
```

**执行过程示例：**

```
nums = [2, 7, 11, 15], target = 9

i = 0: nums[0] = 2
  b = 9 - 2 = 7
  cnt.find(7) -> 未找到
  cnt[2] = 0  // 存储 {2: 0}

i = 1: nums[1] = 7
  b = 9 - 7 = 2
  cnt.find(2) -> 找到了！
  it->first = 2   （键：数字2）
  it->second = 0  （值：索引0）
  return {0, 1}   // 返回 {2的索引, 7的索引}
```

#### 迭代器遍历示例

```cpp
unordered_map<int, int> cnt = {{2, 0}, {7, 1}, {11, 2}};

// 方式1：传统迭代器遍历
for (auto it = cnt.begin(); it != cnt.end(); ++it) {
    cout << "键: " << it->first << ", 值: " << it->second << endl;
}

// 方式2：范围 for 循环（推荐）
for (const auto& [key, value] : cnt) {  // C++17 结构化绑定
    cout << "键: " << key << ", 值: " << value << endl;
}

// 方式3：范围 for 循环（C++11）
for (const auto& p : cnt) {
    cout << "键: " << p.first << ", 值: " << p.second << endl;
}
```

#### 为什么使用迭代器？

1. **统一接口**：不同容器可以用相同方式遍历
2. **灵活性**：可以在遍历过程中修改或删除元素
3. **安全性**：`end()` 提供了明确的边界标记
4. **效率**：直接访问元素，无需索引计算

#### 简化理解：书签类比

最简单的理解方式：

```cpp
auto it = cnt.find(b);  // 查找 b 在哪里

if (it != cnt.end()) {  // 如果找到了
    return {it->second, i};  // 返回 b 对应的值（索引）
}
```

**类比**：
- `it` 就像一个**书签**，标记书中的某个位置
- `it->first` 是这一页的**页码**（键）
- `it->second` 是这一页的**内容**（值）
- `cnt.end()` 是书的**最后一页之后**，表示"没有找到"

#### 迭代器在删除操作中的使用

```cpp
unordered_map<int, int> cnt = {{1, 10}, {2, 20}, {3, 30}};

// 错误：删除元素后继续使用迭代器
for (auto it = cnt.begin(); it != cnt.end(); ++it) {
    if (it->second > 15) {
        cnt.erase(it);  // 迭代器失效
        ++it;  // 未定义行为！
    }
}

// 正确：使用 erase 的返回值
for (auto it = cnt.begin(); it != cnt.end(); ) {
    if (it->second > 15) {
        it = cnt.erase(it);  // 获取下一个有效迭代器
    } else {
        ++it;
    }
}
```

---

### ⭐ 重点理解：cnt[x] 在统计频率中的含义

#### 核心概念

在统计频率的循环中，**访问 `cnt[x]` 时，它表示 x 之前出现的次数**。这是理解哈希表统计功能的关键视角！

#### cnt[x] 的两种含义

| 时间点 | `cnt[x]` 的含义 | 示例 |
|--------|----------------|------|
| **在 `cnt[x]++` 之前访问** | x 之前出现的次数 | `cnt[2] = 1` 表示 2 之前出现过 1 次 |
| **在 `cnt[x]++` 之后访问** | x 当前出现的总次数 | `cnt[2] = 2` 表示 2 总共出现了 2 次 |

#### 统计频率的完整执行过程

```cpp
unordered_map<int, int> cnt;
vector<int> nums = {1, 2, 3, 2, 1, 1};

for (auto& num : nums) {
    cnt[num]++;  // num 作为键，值作为计数
}
```

**详细执行步骤：**

```
步骤1: num = 1
  cnt[1] = 0（默认值，表示 1 之前出现过 0 次）
  cnt[1]++ → cnt[1] = 1
  结果：1 之前出现过 0 次，现在变成 1 次

步骤2: num = 2
  cnt[2] = 0（默认值，表示 2 之前出现过 0 次）
  cnt[2]++ → cnt[2] = 1
  结果：2 之前出现过 0 次，现在变成 1 次

步骤3: num = 3
  cnt[3] = 0（默认值，表示 3 之前出现过 0 次）
  cnt[3]++ → cnt[3] = 1
  结果：3 之前出现过 0 次，现在变成 1 次

步骤4: num = 2  ⭐ 关键时刻
  cnt[2] = 1（表示 2 之前出现过 1 次）
  cnt[2]++ → cnt[2] = 2
  结果：2 之前出现过 1 次，现在变成 2 次

步骤5: num = 1  ⭐ 关键时刻
  cnt[1] = 1（表示 1 之前出现过 1 次）
  cnt[1]++ → cnt[1] = 2
  结果：1 之前出现过 1 次，现在变成 2 次

步骤6: num = 1  ⭐ 关键时刻
  cnt[1] = 2（表示 1 之前出现过 2 次）
  cnt[1]++ → cnt[1] = 3
  结果：1 之前出现过 2 次，现在变成 3 次
```

#### 验证"之前出现的次数"

```cpp
unordered_map<int, int> cnt;
vector<int> nums = {1, 2, 3, 2, 1, 1};

for (int i = 0; i < nums.size(); i++) {
    int num = nums[i];
    
    // 访问 cnt[num] 时，它表示 num 在当前位置之前出现的次数
    cout << "nums[" << i << "] = " << num 
         << ", 之前出现过 " << cnt[num] << " 次" << endl;
    
    cnt[num]++;  // 增加计数
}

// 输出：
// nums[0] = 1, 之前出现过 0 次
// nums[1] = 2, 之前出现过 0 次
// nums[2] = 3, 之前出现过 0 次
// nums[3] = 2, 之前出现过 1 次  ⭐
// nums[4] = 1, 之前出现过 1 次  ⭐
// nums[5] = 1, 之前出现过 2 次  ⭐
```

#### 实际应用：判断是否重复

```cpp
vector<int> nums = {1, 2, 3, 2, 1, 1};
unordered_map<int, int> cnt;

for (int num : nums) {
    if (cnt[num] > 0) {
        // cnt[num] > 0 表示 num 之前出现过
        cout << num << " 是重复元素！" << endl;
    } else {
        // cnt[num] == 0 表示 num 第一次出现
        cout << num << " 是第一次出现" << endl;
    }
    cnt[num]++;
}

// 输出：
// 1 是第一次出现（之前0次）
// 2 是第一次出现（之前0次）
// 3 是第一次出现（之前0次）
// 2 是重复元素！（之前1次）⭐
// 1 是重复元素！（之前1次）⭐
// 1 是重复元素！（之前2次）⭐
```

#### 在两数之和中的应用

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> cnt;  // 存储 {数字: 索引}
    
    for (int i = 0; i < nums.size(); i++) {
        int b = target - nums[i];  // 需要找的补数
        auto it = cnt.find(b);     // 查找补数
        
        if (it != cnt.end()) {
            // 找到了！
            // cnt 中存储的是 {数字: 索引}
            // it->second 是补数之前出现的位置
            return {it->second, i};  // 返回 {之前索引, 当前索引}
        }
        else {
            cnt[nums[i]] = i;  // 存储当前数字及其索引
        }
    }
    return {};
}
```

**理解要点：**
- `cnt[nums[i]] = i` 存储的是 **nums[i] 之前出现的索引**
- 当我们找到补数时，`it->second` 是补数之前出现的位置
- 这正是 `cnt[x]` 表示"之前出现的次数/位置"的体现

#### 关键总结

✅ **重点记忆：**

> 在统计频率的循环中，访问 `cnt[x]` 时，它确实表示 x 之前出现的次数。这是理解哈希表统计功能的关键视角！

**理解这个概念有助于：**
1. 快速判断元素是否重复
2. 理解两数之和等算法的工作原理
3. 掌握哈希表在频率统计中的核心应用

### 10. 自定义类型作为键

```cpp
// 自定义结构体
struct Person {
    string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// 自定义哈希函数
struct PersonHash {
    size_t operator()(const Person& p) const {
        return hash<string>()(p.name) ^ hash<int>()(p.age);
    }
};

// 使用自定义类型作为键
unordered_map<Person, string, PersonHash> personMap;

Person p1{"Alice", 25};
personMap[p1] = "Engineer";

Person p2{"Bob", 30};
personMap[p2] = "Doctor";
```

### 10. 常见应用场景

#### 场景1：两数之和（LeetCode 1）
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;  // 存储值和索引
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (mp.count(complement)) {
            return {mp[complement], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}
```

#### 场景2：字符计数（LeetCode 767）
```cpp
string reorganizeString(string s) {
    unordered_map<char, int> count;
    for (char c : s) {
        count[c]++;
    }

    // 找到出现次数最多的字符
    char maxChar;
    int maxCount = 0;
    for (auto& [c, cnt] : count) {
        if (cnt > maxCount) {
            maxCount = cnt;
            maxChar = c;
        }
    }

    // 检查是否可行
    if (maxCount > (s.size() + 1) / 2) {
        return "";
    }

    // 构建结果
    string result(s.size(), ' ');
    int index = 0;

    // 先放置出现次数最多的字符
    while (count[maxChar] > 0) {
        result[index] = maxChar;
        index += 2;
        count[maxChar]--;
    }

    // 放置其他字符
    for (auto& [c, cnt] : count) {
        while (cnt > 0) {
            if (index >= s.size()) {
                index = 1;
            }
            result[index] = c;
            index += 2;
            cnt--;
        }
    }

    return result;
}
```

#### 场景3：分组字母异位词（LeetCode 49）
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;

    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : mp) {
        result.push_back(group);
    }

    return result;
}
```

#### 场景4：LRU缓存（LeetCode 146）
```cpp
class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;  // 存储键值对
    unordered_map<int, list<pair<int, int>>::iterator> mp;  // 键到链表迭代器的映射

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        // 移动到链表头部
        cache.splice(cache.begin(), cache, mp[key]);
        return mp[key]->second;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            // 更新值并移动到头部
            mp[key]->second = value;
            cache.splice(cache.begin(), cache, mp[key]);
        } else {
            // 添加新元素
            cache.emplace_front(key, value);
            mp[key] = cache.begin();

            // 超出容量，删除最久未使用的
            if (cache.size() > capacity) {
                mp.erase(cache.back().first);
                cache.pop_back();
            }
        }
    }
};
```

---

## 四、unordered_set 详细用法

### 1. 头文件与定义

```cpp
#include <unordered_set>
using namespace std;

// 基本定义
unordered_set<int> st;

// 指定初始大小
unordered_set<int> st(100);

// 自定义哈希函数
struct MyHash {
    size_t operator()(const vector<int>& v) const {
        size_t hash = 0;
        for (int x : v) {
            hash ^= hash * 31 + x;
        }
        return hash;
    }
};
unordered_set<vector<int>, MyHash> st2;
```

### 2. 初始化与赋值

```cpp
// 方式1：逐个插入
unordered_set<int> st;
st.insert(1);
st.insert(2);
st.insert(3);

// 方式2：初始化列表
unordered_set<int> st2 = {1, 2, 3, 4, 5};

// 方式3：从数组初始化
int arr[] = {1, 2, 3, 4, 5};
unordered_set<int> st3(arr, arr + 5);

// 方式4：从 vector 初始化
vector<int> vec = {1, 2, 3, 4, 5};
unordered_set<int> st4(vec.begin(), vec.end());

// 方式5：复制构造
unordered_set<int> st5(st);
```

### 3. 添加元素

```cpp
unordered_set<int> st;

// 方式1：insert()
st.insert(1);
st.insert(2);
st.insert(3);

// 方式2：批量插入
vector<int> vec = {4, 5, 6};
st.insert(vec.begin(), vec.end());

// 方式3：初始化列表插入
st.insert({7, 8, 9});

// 方式4：emplace()（原地构造）
st.emplace(10);

// 注意：重复插入不会生效
st.insert(1);  // 1 已存在，不重复插入
```

### 4. 删除元素

```cpp
unordered_set<int> st = {1, 2, 3, 4, 5};

// 方式1：删除指定值
st.erase(3);

// 方式2：通过迭代器删除
auto it = st.find(2);
if (it != st.end()) {
    st.erase(it);
}

// 方式3：删除范围
st.erase(st.begin(), st.end());  // 清空所有元素

// 方式4：条件删除
for (auto it = st.begin(); it != st.end(); ) {
    if (*it % 2 == 0) {
        it = st.erase(it);
    } else {
        ++it;
    }
}
```

### 5. 查找元素

```cpp
unordered_set<int> st = {1, 2, 3, 4, 5};

// 方式1：find()
auto it = st.find(3);
if (it != st.end()) {
    cout << "Found: " << *it << endl;
}

// 方式2：count()
bool exists = st.count(3);  // 返回 0 或 1
if (exists) {
    cout << "3 exists in the set" << endl;
}

// 方式3：contains()（C++20）
if (st.contains(3)) {
    cout << "3 exists in the set" << endl;
}
```

### 6. 常用操作

```cpp
unordered_set<int> st = {1, 2, 3, 4, 5};

// 大小
int size = st.size();       // 元素个数
bool empty = st.empty();    // 是否为空

// 清空
st.clear();

// 交换两个 set
unordered_set<int> st2;
st.swap(st2);

// 获取迭代器
auto begin = st.begin();    // 第一个元素
auto end = st.end();        // 最后一个元素的下一个位置

// 预留空间
st.reserve(100);

// 获取桶信息
int bucketCount = st.bucket_count();  // 桶的数量
int bucketSize = st.bucket_size(0);   // 指定桶中的元素数量
int bucketIndex = st.bucket(3);       // 元素所在的桶索引

// 加载因子（元素个数 / 桶数量）
float loadFactor = st.load_factor();
float maxLoadFactor = st.max_load_factor();
st.max_load_factor(1.0);  // 设置最大加载因子
```

### 7. 遍历

```cpp
unordered_set<int> st = {1, 2, 3, 4, 5};

// 方式1：范围 for 循环（推荐）
for (int x : st) {
    cout << x << " ";
}
cout << endl;

// 方式2：迭代器遍历
for (auto it = st.begin(); it != st.end(); ++it) {
    cout << *it << " ";
}
cout << endl;

// 方式3：const 迭代器
for (auto it = st.cbegin(); it != st.cend(); ++it) {
    cout << *it << " ";
}
cout << endl;

// 注意：unordered_set 的遍历顺序是不确定的
```

### 8. 集合运算

```cpp
unordered_set<int> set1 = {1, 2, 3, 4, 5};
unordered_set<int> set2 = {4, 5, 6, 7, 8};

// 并集
unordered_set<int> unionSet;
for (int x : set1) unionSet.insert(x);
for (int x : set2) unionSet.insert(x);

// 交集
unordered_set<int> intersectionSet;
for (int x : set1) {
    if (set2.count(x)) {
        intersectionSet.insert(x);
    }
}

// 差集（set1 - set2）
unordered_set<int> differenceSet;
for (int x : set1) {
    if (!set2.count(x)) {
        differenceSet.insert(x);
    }
}

// 对称差集（只在其中一个集合中的元素）
unordered_set<int> symmetricDifferenceSet;
for (int x : set1) {
    if (!set2.count(x)) symmetricDifferenceSet.insert(x);
}
for (int x : set2) {
    if (!set1.count(x)) symmetricDifferenceSet.insert(x);
}
```

### 9. 自定义类型作为元素

```cpp
// 自定义结构体
struct Person {
    string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// 自定义哈希函数
struct PersonHash {
    size_t operator()(const Person& p) const {
        return hash<string>()(p.name) ^ hash<int>()(p.age);
    }
};

// 使用自定义类型
unordered_set<Person, PersonHash> personSet;

Person p1{"Alice", 25};
personSet.insert(p1);

Person p2{"Bob", 30};
personSet.insert(p2);

// 查找
Person p3{"Alice", 25};
if (personSet.count(p3)) {
    cout << "Found Alice" << endl;
}
```

### 10. 常见应用场景

#### 场景1：去重
```cpp
vector<int> removeDuplicates(vector<int>& nums) {
    unordered_set<int> seen;
    vector<int> result;

    for (int num : nums) {
        if (seen.count(num) == 0) {
            seen.insert(num);
            result.push_back(num);
        }
    }

    return result;
}
```

#### 场景2：判断存在性（LeetCode 128）
```cpp
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longestStreak = 0;

    for (int num : numSet) {
        // 只从序列的开头开始
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentStreak = 1;

            while (numSet.count(currentNum + 1)) {
                currentNum++;
                currentStreak++;
            }

            longestStreak = max(longestStreak, currentStreak);
        }
    }

    return longestStreak;
}
```

#### 场景3：寻找重复元素（LeetCode 287）
```cpp
int findDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) {
            return num;
        }
        seen.insert(num);
    }
    return -1;
}
```

#### 场景4：两个数组的交集（LeetCode 349）
```cpp
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> resultSet;

    for (int num : nums2) {
        if (set1.count(num)) {
            resultSet.insert(num);
        }
    }

    return vector<int>(resultSet.begin(), resultSet.end());
}
```

#### 场景5：单词拆分（LeetCode 139）
```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}
```

#### 场景6：快乐数（LeetCode 202）
```cpp
bool isHappy(int n) {
    unordered_set<int> seen;

    while (n != 1 && !seen.count(n)) {
        seen.insert(n);
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }

    return n == 1;
}
```

---

## 五、unordered_map 和 unordered_set 的混合使用

### 1. 统计频率并去重
```cpp
vector<pair<int, int>> countAndSort(vector<int>& nums) {
    unordered_map<int, int> countMap;
    unordered_set<int> uniqueSet;

    // 统计频率并去重
    for (int num : nums) {
        countMap[num]++;
        uniqueSet.insert(num);
    }

    // 转换为 vector
    vector<pair<int, int>> result;
    for (int num : uniqueSet) {
        result.push_back({num, countMap[num]});
    }

    // 按频率排序
    sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return result;
}
```

### 2. 使用 set 辅助 map 操作
```cpp
vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> countMap;

    // 统计频率
    for (string& word : words) {
        countMap[word]++;
    }

    // 使用自定义排序的 set
    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    };

    set<pair<string, int>, decltype(cmp)> sortedWords(cmp);
    for (auto& [word, count] : countMap) {
        sortedWords.insert({word, count});
    }

    // 获取前 k 个
    vector<string> result;
    auto it = sortedWords.begin();
    for (int i = 0; i < k && it != sortedWords.end(); i++, ++it) {
        result.push_back(it->first);
    }

    return result;
}
```

### 3. 双重哈希表（图去重）
```cpp
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;

    int m = grid.size();
    int n = grid[0].size();
    unordered_set<int> visited;

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1' && !visited.count(i * n + j)) {
                count++;
                // BFS
                queue<int> q;
                q.push(i * n + j);
                visited.insert(i * n + j);

                while (!q.empty()) {
                    int pos = q.front();
                    q.pop();
                    int x = pos / n;
                    int y = pos % n;

                    // 四个方向
                    int dx[] = {-1, 1, 0, 0};
                    int dy[] = {0, 0, -1, 1};

                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        int newPos = nx * n + ny;

                        if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                            grid[nx][ny] == '1' && !visited.count(newPos)) {
                            visited.insert(newPos);
                            q.push(newPos);
                        }
                    }
                }
            }
        }
    }

    return count;
}
```

---

## 六、性能优化建议

### 1. 预分配空间
```cpp
// 如果知道大概的元素数量，预分配空间
unordered_map<int, int> mp;
mp.reserve(10000);  // 预留空间，减少重新哈希

unordered_set<int> st;
st.reserve(10000);
```

### 2. 选择合适的数据类型
```cpp
// 使用 int 而不是 long long（如果范围允许）
unordered_map<int, int> mp;  // 好
unordered_map<long long, int> mp2;  // 慢

// 使用 string_view（C++17）代替 string
unordered_map<string_view, int> mp3;
```

### 3. 避免频繁的 insert/erase
```cpp
// 批量操作
vector<pair<int, int>> data = {{1, 10}, {2, 20}, {3, 30}};
unordered_map<int, int> mp(data.begin(), data.end());  // 好

// 不好的做法
unordered_map<int, int> mp;
for (auto& [k, v] : data) {
    mp.insert({k, v});  // 慢
}
```

### 4. 使用 emplace 代替 insert
```cpp
unordered_map<string, int> mp;

// 好
mp.emplace("hello", 1);

// 不太好
mp.insert({"hello", 1});

// 更不好
mp["hello"] = 1;  // 会先创建默认值再赋值
```

### 5. 使用 count 代替 find
```cpp
unordered_map<int, int> mp;

// 简洁
if (mp.count(1)) {
    // 存在
}

// 冗长
if (mp.find(1) != mp.end()) {
    // 存在
}
```

### 6. 调整加载因子
```cpp
unordered_map<int, int> mp;

// 设置较小的加载因子，减少哈希冲突，但占用更多内存
mp.max_load_factor(0.5);

// 设置较大的加载因子，节省内存，但可能增加哈希冲突
mp.max_load_factor(2.0);
```

---

## 七、常见陷阱与注意事项

### 1. 迭代器失效
```cpp
unordered_map<int, int> mp = {{1, 10}, {2, 20}, {3, 30}};

// 错误：删除元素后继续使用迭代器
for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it->second > 15) {
        mp.erase(it);  // 迭代器失效
        ++it;  // 未定义行为！
    }
}

// 正确：使用 erase 的返回值
for (auto it = mp.begin(); it != mp.end(); ) {
    if (it->second > 15) {
        it = mp.erase(it);  // 获取下一个有效迭代器
    } else {
        ++it;
    }
}
```

### 2. 自定义类型需要重载 == 和哈希函数
```cpp
// 错误：没有提供哈希函数
struct Point {
    int x, y;
};
unordered_set<Point> st;  // 编译错误！

// 正确：提供哈希函数
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

unordered_set<Point, PointHash> st;  // 正确
```

### 3. unordered_map 的 [] 运算符会创建默认值
```cpp
unordered_map<int, string> mp;

// 错误：意外创建默认值
if (mp[99] == "value") {  // mp[99] 被创建，value=""（string默认值）
    // ...
}

// 正确：使用 count 或 find
if (mp.count(99) && mp[99] == "value") {
    // ...
}
```

### 4. 遍历顺序不确定
```cpp
unordered_set<int> st = {1, 2, 3, 4, 5};

// 错误：依赖遍历顺序
vector<int> result(st.begin(), st.end());  // 顺序不确定

// 如果需要有序，使用 set 或排序后
set<int> sortedSet(st.begin(), st.end());
vector<int> sortedResult(sortedSet.begin(), sortedSet.end());
```

### 5. 哈希冲突导致性能下降
```cpp
// 错误：大量哈希冲突
unordered_map<int, int> mp;
for (int i = 0; i < 10000; i++) {
    mp[i * 10000] = i;  // 如果哈希函数不好，可能导致冲突
}

// 解决：使用好的哈希函数或调整加载因子
```

---

## 八、LeetCode 经典题目总结

### 使用 unordered_map 的经典题目
1. **两数之和（1）** - 查找补数
2. **三数之和（15）** - 避免重复
3. **四数之和（18）** - 双指针优化
4. **字母异位词分组（49）** - 排序作为键
5. **最长连续序列（128）** - 并查集思想
6. **LRU缓存（146）** - 链表+哈希表
7. **同构字符串（205）** - 映射关系
8. **单词模式（290）** - 双向映射
9. **克隆图（133）** - 记录访问节点
10. **前K个高频元素（347）** - 统计频率

### 使用 unordered_set 的经典题目
1. **存在重复元素（217）** - 简单去重
2. **只出现一次的数字（136）** - 异或或集合
3. **两个数组的交集（349）** - 集合交集
4. **两个数组的交集II（350）** - 统计频率
5. **快乐数（202）** - 检测循环
6. **单词拆分（139）** - 动态规划
7. **岛屿数量（200）** - BFS/DFS
8. **有效的数独（36）** - 行列块检查
9. **最长无重复子串（3）** - 滑动窗口
10. **环形链表（141）** - 快慢指针或哈希表

### 混合使用的经典题目
1. **设计推特（355）** - 用户+推文
2. **设计插入删除获取随机O(1)（380）** - 数组+哈希表
3. **实现Trie（208）** - 字典树
4. **前K个高频单词（692）** - 频率+字典序
5. **账户合并（721）** - 并查集+哈希表

---

## 九、总结

### 何时使用 unordered_map
- 需要存储键值对
- 需要通过键快速查找对应的值
- 需要建立映射关系

### 何时使用 unordered_set
- 只需要存储键，不需要值
- 需要去重
- 需要快速判断元素是否存在

### 性能对比
- **unordered_map/set**：O(1) 平均查找，O(n) 最坏
- **map/set**：O(log n) 查找，有序
- **vector**：O(n) 查找，但缓存友好

### 选择建议
1. 需要有序 → map/set
2. 需要稳定 O(1) 查找 → map/set
3. 需要最快查找且不需要有序 → unordered_map/set
4. 数据量小 → vector 可能更快
5. 频繁插入/删除 → unordered_map/set

---

## 十、练习建议

1. **基础操作**：熟练掌握插入、删除、查找、遍历
2. **经典题目**：按顺序刷 LeetCode 经典题
3. **性能优化**：学会预分配空间、选择合适类型
4. **复杂应用**：结合其他数据结构使用
5. **自定义类型**：掌握自定义哈希函数

### 推荐刷题顺序
1. 简单题目（熟悉基本操作）
   - 两数之和（1）
   - 存在重复元素（217）
   - 只出现一次的数字（136）

2. 中等题目（掌握常见模式）
   - 字母异位词分组（49）
   - 最长连续序列（128）
   - 单词拆分（139）

3. 困难题目（综合应用）
   - LRU缓存（146）
   - 设计推特（355）
   - 账户合并（721）

每种操作建议练习5-10道题，熟练后再进行下一阶段的学习。