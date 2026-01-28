# LeetCode 第一阶段：基础数据结构操作手册

## 数组

### 1. 初始化与创建

```cpp
// 静态数组
int arr[5] = {1, 2, 3, 4, 5};
int arr2[10];  // 未初始化

// 动态数组
vector<int> v;
vector<int> v2 = {1, 2, 3, 4, 5};
vector<int> v3(10, 0);  // 10个元素，全部初始化为0
vector<int> v4(5);      // 5个元素，默认值为0
vector<vector<int>> matrix(3, vector<int>(4, 0));  // 3x4矩阵
```

### 2. 遍历

```cpp
// 下标遍历
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

// 范围for循环（推荐）
for (int num : v) {
    cout << num << " ";
}

// 迭代器遍历
for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
}

// 二维数组遍历
for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
        cout << matrix[i][j] << " ";
    }
}
```

### 3. 常用操作

```cpp
vector<int> v = {1, 2, 3};

// 访问元素
int x = v[0];           // 下标访问
int y = v.front();      // 第一个元素
int z = v.back();       // 最后一个元素
int n = v.at(0);        // 带边界检查的访问

// 添加元素
v.push_back(4);         // 末尾添加
v.insert(v.begin(), 0); // 任意位置插入
v.insert(v.begin(), 3, 100); // 插入3个100

// 删除元素
v.pop_back();           // 删除末尾
v.erase(v.begin());     // 删除第一个
v.erase(v.begin(), v.begin() + 2); // 删除前两个

// 大小相关
int size = v.size();    // 元素个数
bool empty = v.empty(); // 是否为空
v.clear();              // 清空数组

// 调整大小
v.resize(10);           // 调整大小，新增元素默认为0
v.resize(10, 5);        // 调整大小，新增元素初始化为5
v.reserve(20);          // 预分配空间（不改变size）
```

### 4. 排序

```cpp
vector<int> v = {5, 2, 8, 1, 9};

// 升序排序
sort(v.begin(), v.end());

// 降序排序
sort(v.rbegin(), v.rend());
// 或
sort(v.begin(), v.end(), greater<int>());

// 自定义排序
sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b);  // 按绝对值排序
});

// 部分排序
sort(v.begin(), v.begin() + 3);  // 只排序前3个

// 乱序
random_shuffle(v.begin(), v.end());
```

### 5. 查找

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// 线性查找
auto it = find(v.begin(), v.end(), 3);
if (it != v.end()) {
    cout << "Found at index: " << (it - v.begin()) << endl;
}

// 二分查找（数组必须有序）
bool found = binary_search(v.begin(), v.end(), 3);

// 二分查找位置
auto lower = lower_bound(v.begin(), v.end(), 3);  // 第一个>=3的位置
auto upper = upper_bound(v.begin(), v.end(), 3);  // 第一个>3的位置

// 统计元素个数
int count = std::count(v.begin(), v.end(), 3);
```

### 6. 双指针操作（LeetCode高频）

```cpp
// 对撞指针（从两端向中间）
int left = 0, right = v.size() - 1;
while (left < right) {
    int sum = v[left] + v[right];
    if (sum == target) {
        return {left, right};
    } else if (sum < target) {
        left++;
    } else {
        right--;
    }
}

// 快慢指针（链表、环检测）
int slow = 0, fast = 0;
while (fast < v.size()) {
    slow += 1;
    fast += 2;
}

// 滑动窗口
int left = 0;
for (int right = 0; right < v.size(); right++) {
    // 扩大窗口
    while (windowSum > target) {
        // 缩小窗口
        windowSum -= v[left];
        left++;
    }
}
```

### 7. 前缀和（LeetCode高频）

```cpp
vector<int> v = {1, 2, 3, 4, 5};
int n = v.size();

// 构建前缀和数组
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + v[i];
}

// 查询区间和 [l, r]
int sum = prefix[r + 1] - prefix[l];

// 二维前缀和
vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int m = matrix.size(), n = matrix[0].size();
vector<vector<int>> prefix2d(m + 1, vector<int>(n + 1, 0));

for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        prefix2d[i][j] = prefix2d[i-1][j] + prefix2d[i][j-1] 
                        - prefix2d[i-1][j-1] + matrix[i-1][j-1];
    }
}

// 查询矩形区域和 [x1,y1] 到 [x2,y2]
int sum = prefix2d[x2+1][y2+1] - prefix2d[x1][y2+1] 
        - prefix2d[x2+1][y1] + prefix2d[x1][y1];
```

### 8. 旋转数组

```cpp
// 反转整个数组
reverse(v.begin(), v.end());

// 反转部分数组
reverse(v.begin(), v.begin() + 3);

// 旋转数组（向右移动k步）
k = k % v.size();
reverse(v.begin(), v.end());
reverse(v.begin(), v.begin() + k);
reverse(v.begin() + k, v.end());
```

### 9. 去重

```cpp
// 排序后去重
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

// 统计不重复元素个数
int uniqueCount = unique(v.begin(), v.end()) - v.begin();
```

### 10. 交换元素

```cpp
swap(v[0], v[1]);  // 交换两个元素
reverse(v.begin(), v.end());  // 反转数组
rotate(v.begin(), v.begin() + 2, v.end());  // 左旋2位
```

---

## 字符串

### 1. 初始化与创建

```cpp
// 基本初始化
string s1 = "hello";
string s2("world");
string s3(5, 'a');  // "aaaaa"
string s4(s1);      // 复制构造

// 从其他类型转换
string s5 = to_string(123);  // "123"
int num = stoi("123");       // 123
double d = stod("3.14");     // 3.14
```

### 2. 遍历

```cpp
string s = "hello";

// 下标遍历
for (int i = 0; i < s.size(); i++) {
    cout << s[i];
}

// 范围for循环
for (char c : s) {
    cout << c;
}

// 修改字符
for (char &c : s) {
    c = toupper(c);
}
```

### 3. 常用操作

```cpp
string s = "hello world";

// 访问字符
char first = s[0];
char last = s.back();
char second = s.at(1);

// 大小
int len = s.length();  // 或 s.size()
bool empty = s.empty();

// 拼接
string s1 = "hello", s2 = "world";
string s3 = s1 + " " + s2;
s1 += " world";

// 查找
int pos = s.find("world");     // 返回位置，找不到返回 string::npos
int pos2 = s.find("o", 5);     // 从位置5开始查找
int pos3 = s.rfind("o");       // 从后往前查找

// 比较大小
if (s1 == s2) { }
if (s1 < s2) { }  // 字典序比较

// 清空
s.clear();
```

### 4. 子串操作

```cpp
string s = "hello world";

// 获取子串
string sub = s.substr(0, 5);  // "hello"（从位置0开始，长度5）
string sub2 = s.substr(6);    // "world"（从位置6到末尾）

// 替换子串
s.replace(6, 5, "everyone");  // "hello everyone"

// 插入
s.insert(5, " my");  // "hello my world"

// 删除
s.erase(5, 3);  // 删除从位置5开始的3个字符
```

### 5. 字符处理

```cpp
string s = "Hello World 123";

// 判断字符
isalpha('a');   // 是否为字母
isdigit('1');   // 是否为数字
islower('a');   // 是否为小写
isupper('A');   // 是否为大写
isspace(' ');   // 是否为空格

// 转换字符
tolower('A');   // 'a'
toupper('a');   // 'A'

// 字符串大小写转换
transform(s.begin(), s.end(), s.begin(), ::tolower);
transform(s.begin(), s.end(), s.begin(), ::toupper);
```

### 6. 分割字符串

```cpp
string s = "hello,world,leetcode";
vector<string> result;
stringstream ss(s);
string token;

// 按逗号分割
while (getline(ss, token, ',')) {
    result.push_back(token);
}

// 按空格分割
string s2 = "hello world leetcode";
stringstream ss2(s2);
while (ss2 >> token) {
    result.push_back(token);
}
```

### 7. 字符串匹配

```cpp
string text = "hello world";
string pattern = "world";

// 查找位置
size_t pos = text.find(pattern);
if (pos != string::npos) {
    cout << "Found at: " << pos << endl;
}

// 统计出现次数
int count = 0;
size_t start = 0;
while ((start = text.find(pattern, start)) != string::npos) {
    count++;
    start += pattern.length();
}

// 判断是否包含
bool contains = text.find(pattern) != string::npos;
```

### 8. 字符串反转

```cpp
string s = "hello";

// 反转整个字符串
reverse(s.begin(), s.end());  // "olleh"

// 反转部分字符串
reverse(s.begin(), s.begin() + 3);  // "lehlo"
```

### 9. 去除首尾空白

```cpp
string s = "  hello world  ";

// 去除首尾空格
s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);

// 去除所有空格
s.erase(remove(s.begin(), s.end(), ' '), s.end());
```

### 10. 判断回文

```cpp
string s = "aba";

// 方法1：反转后比较
bool isPalindrome1 = (s == string(s.rbegin(), s.rend()));

// 方法2：双指针
bool isPalindrome2 = true;
int left = 0, right = s.size() - 1;
while (left < right) {
    if (s[left] != s[right]) {
        isPalindrome2 = false;
        break;
    }
    left++;
    right--;
}

// 方法3：只考虑字母数字（忽略大小写和符号）
bool isPalindrome3(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }
    return true;
}
```

### 11. 最长公共子串

```cpp
// 动态规划方法
string longestCommonSubstring(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0, endIndex = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;
                }
            }
        }
    }
    return s1.substr(endIndex - maxLength, maxLength);
}
```

### 12. 字符串的全排列

```cpp
// 生成所有排列
vector<string> permutations(string s) {
    vector<string> result;
    sort(s.begin(), s.end());
    do {
        result.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    return result;
}
```

---

## 链表

### 1. 链表节点定义

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

### 2. 创建链表

```cpp
// 从数组创建链表
ListNode* createList(vector<int>& arr) {
    if (arr.empty()) return nullptr;
    
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    
    for (int i = 1; i < arr.size(); i++) {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    return head;
}

// 创建单个节点
ListNode* node = new ListNode(5);
```

### 3. 遍历链表

```cpp
// 基本遍历
void traverse(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
}

// 使用for循环遍历
for (ListNode* p = head; p != nullptr; p = p->next) {
    cout << p->val << " ";
}
```

### 4. 查找节点

```cpp
// 按值查找
ListNode* findNode(ListNode* head, int target) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->val == target) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// 查找倒数第k个节点
ListNode* findKthFromEnd(ListNode* head, int k) {
    ListNode* fast = head;
    ListNode* slow = head;
    
    // fast先走k步
    for (int i = 0; i < k; i++) {
        if (fast == nullptr) return nullptr;
        fast = fast->next;
    }
    
    // 同时移动
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    
    return slow;
}
```

### 5. 插入节点

```cpp
// 在头部插入
ListNode* insertAtHead(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    return newNode;
}

// 在尾部插入
ListNode* insertAtTail(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    
    if (head == nullptr) {
        return newNode;
    }
    
    ListNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// 在指定节点后插入
void insertAfter(ListNode* node, int val) {
    if (node == nullptr) return;
    ListNode* newNode = new ListNode(val);
    newNode->next = node->next;
    node->next = newNode;
}

// 在指定位置插入（从0开始）
ListNode* insertAtIndex(ListNode* head, int index, int val) {
    if (index < 0) return head;
    
    if (index == 0) {
        return insertAtHead(head, val);
    }
    
    ListNode* current = head;
    for (int i = 0; i < index - 1 && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current == nullptr) return head;
    
    insertAfter(current, val);
    return head;
}
```

### 6. 删除节点

```cpp
// 删除头节点
ListNode* deleteAtHead(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode* newHead = head->next;
    delete head;
    return newHead;
}

// 删除尾节点
ListNode* deleteAtTail(ListNode* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }
    
    ListNode* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    
    delete current->next;
    current->next = nullptr;
    return head;
}

// 删除指定节点（只知道该节点，不知道头节点）
void deleteNode(ListNode* node) {
    if (node == nullptr || node->next == nullptr) return;
    
    ListNode* nextNode = node->next;
    node->val = nextNode->val;
    node->next = nextNode->next;
    delete nextNode;
}

// 删除指定值的节点
ListNode* deleteByValue(ListNode* head, int val) {
    // 处理头节点
    while (head != nullptr && head->val == val) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    
    if (head == nullptr) return nullptr;
    
    ListNode* current = head;
    while (current->next != nullptr) {
        if (current->next->val == val) {
            ListNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    
    return head;
}

// 删除倒数第k个节点
ListNode* deleteKthFromEnd(ListNode* head, int k) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* fast = dummy;
    ListNode* slow = dummy;
    
    for (int i = 0; i <= k; i++) {
        if (fast == nullptr) return head;
        fast = fast->next;
    }
    
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    
    ListNode* temp = slow->next;
    slow->next = temp->next;
    delete temp;
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}
```

### 7. 反转链表

```cpp
// 迭代法
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current != nullptr) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

// 递归法
ListNode* reverseListRecursive(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
}

// 反转部分链表 [m, n]
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    // 找到第m-1个节点
    for (int i = 1; i < m; i++) {
        prev = prev->next;
    }
    
    ListNode* current = prev->next;
    
    // 反转n-m+1个节点
    for (int i = m; i < n; i++) {
        ListNode* next = current->next;
        current->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    
    return dummy->next;
}
```

### 8. 快慢指针（环检测）

```cpp
// 检测链表是否有环
bool hasCycle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return false;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }
    
    return false;
}

// 找到环的入口节点
ListNode* detectCycle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 检测是否有环
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            break;
        }
    }
    
    if (fast == nullptr || fast->next == nullptr) {
        return nullptr;
    }
    
    // 找到环的入口
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}

// 找到链表中点
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

### 9. 合并链表

```cpp
// 合并两个有序链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    
    current->next = (l1 != nullptr) ? l1 : l2;
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

// 合并K个有序链表
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    while (lists.size() > 1) {
        vector<ListNode*> merged;
        for (int i = 0; i < lists.size(); i += 2) {
            if (i + 1 < lists.size()) {
                merged.push_back(mergeTwoLists(lists[i], lists[i+1]));
            } else {
                merged.push_back(lists[i]);
            }
        }
        lists = merged;
    }
    
    return lists[0];
}
```

### 10. 释放链表内存

```cpp
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}
```

### 11. 回文链表判断

```cpp
bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    
    // 找到中点
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 反转后半部分
    ListNode* secondHalf = reverseList(slow->next);
    
    // 比较
    ListNode* p1 = head;
    ListNode* p2 = secondHalf;
    bool result = true;
    while (p2 != nullptr) {
        if (p1->val != p2->val) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    // 恢复链表
    slow->next = reverseList(secondHalf);
    
    return result;
}
```

### 12. 旋转链表

```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) return head;
    
    // 计算链表长度并连接成环
    int len = 1;
    ListNode* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
        len++;
    }
    tail->next = head;
    
    // 找到新的尾节点
    k = k % len;
    int steps = len - k;
    ListNode* newTail = tail;
    while (steps > 0) {
        newTail = newTail->next;
        steps--;
    }
    
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    
    return newHead;
}
```

---

## LeetCode 常见模式总结

### 数组常见模式

1. **双指针** - 数组去重、两数之和、三数之和
2. **滑动窗口** - 最长子串、最小窗口
3. **前缀和** - 区间和查询、子数组问题
4. **排序** - 排序后处理、去重
5. **二分查找** - 有序数组查找

### 字符串常见模式

1. **KMP算法** - 字符串匹配
2. **双指针** - 回文判断、字符串反转
3. **滑动窗口** - 最长不重复子串
4. **哈希表** - 字符统计、异位词

### 链表常见模式

1. **快慢指针** - 环检测、找中点
2. **反转链表** - 多种反转场景
3. **哑节点** - 简化头节点处理
4. **递归** - 反转、合并

---

## 练习建议

1. **先掌握基础操作**：创建、遍历、插入、删除
2. **重点练习指针操作**：反转、合并、环检测
3. **掌握常用模式**：双指针、滑动窗口、快慢指针
4. **多刷经典题目**：两数之和、反转链表、最长回文串等

每种操作建议练习5-10道题，熟练后再进行下一阶段的学习。