# C++ stl: heap、priority_queue

# stl heap 堆

下面的函数直接操作 heap，较底层，通常不直接使用。

```cpp
#include <algorithm>

std::make_heap(first, last)
// 建堆

std::push_heap(first, last)
// 往堆里添一个元素
// 添加前，heap 范围是 [first, last-1)。随后的那个元素（即 last-1 位置处）是待添加的元素。
// 添加：把 last-1 位置的元素放入 heap 里。
// 添加后：heap 范围扩大到 [first, last)。

std::pop_heap(first, last)
// 删除堆顶元素（first 位置的）
// 删除前：[first, last) 范围是已排好序的 heap。
// 删：first 和 last-1 位置元素对调，再 heapify [first, last-1] 范围。
// 删除后：原堆顶（first 位置的）到了 last-1 位置。

std::is_heap(first, last)
// 顾名思义

std::sort_heap(first, last)
// 把 [first, last) 范围的堆，排序。排序后，就不是堆了。
```

堆排序的可能实现方法

```cpp
void sort_heap(RandomIt first, RandomIt last, Compare comp) {
    while (first != last) {
        std::pop_heap(first, last--, comp);
    }
}
```

# STL priority_queue 优先级队列

```cpp
#include <queue>
std::priority_queue
```

priority_queue 类，是个 container adaptor。底层可用 vector 或 queue，STL 缺省用 vector。缺省是 max heap。

成员函数（只有这些！）：
* 入队(堆): `push()`, `emplace()`。不是放在队尾，而是放入后排序。
* 访问队头(堆顶): `top()`, `pop()`。不能访问队尾（堆底）。
* `empty()`, `size()`
* `swap()`: 跟另一个 pq 交换内容。(为何需要此功能？)

## STL priority_queue 代码例子

用三种方法创建的 pq，缺省是 max heap，都已经排好序。遍历输出，可见从 9 到 0。

若查看内部 container (vector)，则其顺序为 `9 8 5 7 3 4 0 1 6 2`。

遍历时，逐个访问并弹出 top 元素。遍历完后，pq 也空了。（不推荐的方法：直接访问内部的 container。代码略。）

```cpp
void print_pq(priority_queue<int> pq) {
    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << endl;
}

int main() {
    const vector v = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    const int a[] = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
 
    // 法一，缺省max堆，逐个push元素
    priority_queue<int> maxq1;
    for (int n : v) { maxq1.push(n); }

    // 法二，缺省max堆，从vector创建pq
    priority_queue<int> maxq2(v.begin(), v.end());

    // 法三，缺省max堆，从数组创建pq 
    priority_queue<int> maxq3(a, a + sizeof a / sizeof(int));

    // 法一：min堆，从vector建pq。类型中指定比较函数，参数中则不用指定。
    priority_queue<int, vector<int>, greater<int>> minq1(v.begin(), v.end());

    // 法二：min堆，从vector建pq。类型中不指定比较函数，参数中则指定。
    priority_queue minq2(v.begin(), v.end(), greater<int>());

    // 法三：min堆，从数组建pq。
    priority_queue minq3(a, a + sizeof a / sizeof(int), greater<int>());

    // 法四：自定义 functor 作为比较函数。
    struct my_less {
      bool operator()(const int l, const int r) const { return l > r; }
    };
    priority_queue q4(v.begin(), v.end(), my_less);

    // 法五：用 lambda 作为比较函数
    auto my_cmp = [](int l, int r) { return (l ^ 1) < (r ^ 1); };
    priority_queue<int, vector<int>, decltype(my_cmp)> q5(my_cmp);
    for (int n : v) { q5.push(n); }
}
```

## priority queue 元素比较

原则：若 `a < b`，则 b 更靠近堆顶。因缺省是 max-heap，堆顶是最大的。

注意：max-heap，每次 pop() 出来的是最大的，则堆排序的结果恰好是从小到大。

概述：

方法 | 是否需改对象数据结构 | 创建 pq 时是否需提供comparator 参数
----|----|----
1, 定义独立的 `operator<(T a, T b)` | N | N
2, 定义独立的比较函数 `my_cmp(T a, T b)` | N | Y. `my_cmp`
3, 定义独立的 lambda 做比较函数 | N | Y. `decltype(my_cmp)`
4, 定义独立的 functor (struct/class)，其中重载 `operator(T a, T b)` | N | Y. `functor_name`
5, 对象 struct/class 内重载 `operator<(T other)` | Y | N
6, 对象 class 内重载 `friend operator<(T a, T b)` | Y | N

### 1. 定义独立的 `bool operator<(const T& a, const T& b)`

最方便。完整代码：[pq_standalone_optr_lt.cpp](code/pq_standalone_optr_lt.cpp)

```cpp
struct Person { ... }

bool operator<(const Person& p1, const Person& p2) {
    return p1.height < p2.height;
}

priority_queue<Person> pq;
priority_queue<Person> pq(v.begin(), v.end());
```

### 4. 独立的 functor (struct/class)，其中重载 `bool operator()(const T& a, const T& b)`

struct/class 二者唯一区别，就是 class 里的 operator() 要声明为 public 的。

被比较的对象，也可以是 struct 或 class，区别同上。

```cpp
struct Person { ... }

// struct functor
struct CompareHeight {
  bool operator()(Person const& p1, Person const& p2) {
    return p1.height < p2.height;
  }
};

// 或 class functor, operator() 要声明为 public 的。
class CompareHeight {
public:
  bool operator()(Person const& p1, Person const& p2) {
    return p1.height < p2.height;
  }
};

priority_queue<Person, vector<Person>, CompareHeight> pq;
```

为了能在 operator() 里访问 class 对象的成员，要把成员变量声明为 public 的，或增加 public 的 getter 函数。

```cpp
class Person {
  int age; float height;
public:
  int getAge() const { return age; }
  float getHeight() const { return height; }
  Person(int age, float height) : age(age), height(height) { }
};
```

### 5：对象 class/struct 重载 `bool operator<(const T& other) const`

两者比较，但 `operator<` 的参数只有一个，是第二个被比较者。struct/class 对象自己是隐藏的第一个被比较者。

```cpp
struct Person {
  int age; float height;
  Person(int a, float h): age(a), height(h) {}
  bool operator<(const Person& other) const {
    return height < other.height;
  }
};
priority_queue<Person> pq;
```

class，与 struct 几乎一样。但构造函数和 `operator<()` 要声明为 public 的。age/height 两个成员变量倒不用是 public 的。

```cpp
class Person {
  public:
    int age; float height;
    Person(int age, float height): age(age), height(height) { }
    bool operator<(const Person& other) const {
      return this->height < other.height;  // ‘this->’ 也可不要
    }
};
priority_queue<Person> pq;
```

### 6. 对象 class 内定义 `friend bool operator<(const T& a, const T& b)`

class，`operator<()` 声明为 friend 函数。两个参数，也不能用 const 修饰。

友元函数：不是类的成员函数，但可访问类的 private、protected 成员。友元函数的原型要在类定义中出现，定义可在类外。

```cpp
class Person {
  public:
    int age; float height;
    Person(int ag, float h): age(ag), height(h) {}
    friend bool operator<(const Person& p1, const Person &p2) {
      return p1.height < p2.height;
    }
};
priority_queue<Person> pq;
```
