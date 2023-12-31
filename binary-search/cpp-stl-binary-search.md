# C++ STL 提供的 binary search 函数

# lower_bound()、upper_bound()

```cpp
    #include <algorithm>

    lower_bound(first, last, k); // 找第一个「大于等于 k」的元素
    upper_bound(first, last, k); // 找第一个「大于 k」的元素
```

遵循 STL algorithm 的规范，搜索的范围是左闭右开区间 `[first, last)`。

last 不在范围之内。或者说，last 是「最大下标 + 1」、「最后位置之后」。

对于数组，
```cpp
    int a[] = { 5, 7, 9, 9, 9, 9, 11, 13 };
    int size = sizeof a / sizeof(int);
    int *p = lower_bound(a, a + size, 5);
    // 数组下标从 0 到 size - 1. last 值为 size，就是“最大下标 +1”.
    long index = p – a;	// 结果的下标
```

对于 container (例如 vector)，
```cpp
    vector<int> v = { 5, 7, 9, 9, 9, 9, 11, 13 }; // c++11
    vector<int>::iterator it = lower_bound(v.begin(), v.end(), 5);
    // v.end() 就是“最后元素之后”
    long index = it – v.begin();   // 结果的下标
```

返回值：
- 若 k 不存在，且 k 大于数组中最大值，则返回值为 `size` 或 `v.end()`, 即「最后元素之后」。
- 若 k 不存在，返回值可以理解为：如果 k 放入数组，应该放在什么位置。

# equal_range()

```cpp
    p = equal_range(first, last, k); // 找 k 的范围；相当于 lower_bound 和 upper_bound 的组合。
```

返回值是个 pair，意思为
- `[第一个 k 的位置，最后一个 k 的位置之后)`，或 `[第一个 k 的位置，第一个大于 k 的位置)`
- 若 k 不存在，则返回的两个数一样，都是「第一个大于 k 的位置」
- k 在数组内的范围是 `[p.first, p.second)` 区间。这个范围，左闭右开，也是遵循 STL 传统的。

用法
```cpp
    pair<int *, int *> p = equal_range(a, a + size, k);
    long id1 = p.first - a;
    long id2 = p.second - a;

    pair<vector<int>::iterator, vector<int>::iterator> p = equal_range(a.begin(), a.end(), k);
    long id1 = p.first - a.begin();
    long id2 = p.second - a.begin();
```

# 简单数据类型，使用比较函数

```cpp
    vector<int> v = {10, 9, 7, 5, 3, 1};                   
    auto it = lower_bound(v.begin(), v.end(), 8, greater<int>()); 
    int pos = it - v.begin();
```

# 结构体类型，使用比较函数

如果是两个结构体<font color="green">直接</font>比较，则可用普通的比较函数，类似 `sort()` 里用到的那样。此时需要自己构造一个 student 的 dummy 对象用于比较：

```cpp
    struct student {
        string name;
        int age;
        int grade;
    };

    bool cmp(const student &s1, const student &s2) {
        return s1.age < s2.age;
    }

    student s;
    s.age = 13;                   
    auto it = lower_bound(v.begin(), v.end(), s, cmp); 
    int pos = it - v.begin();
```

但通常，第一个参数里是要比较的字段的值，而不是结构体对象。以 student 结构体为例，要比较 age，所以第一个参数是 int 类型；第二个参数才是 student 类型。

法一：自定义函数。`upper_bound()` 调用时，函数名后不用加括号。

```cpp
    bool student_cmp(int age, student const &t) {
        return age < t.age;
    }
    it = upper_bound(v.begin(), v.end(), 11, student_cmp);
```

法二：重载小于比较符。`upper_bound()` 调用时，不用带比较函数名。

```cpp
    bool operator <(int age, student const &t) {
        return age < t.age;
    }
    it = upper_bound(v.begin(), v.end(), 11);
```

法三：使用 functor.

Functor 就是重载了 `operator()` 的 class 或 struct。可以当做函数使用。`upper_bound()` 调用时，functor 名后要加括号。

```cpp
    struct student_cmp {
        bool operator ()(int age, const student &t) const {
            return age < t.age;
        }
    };
    it = upper_bound(v.begin(), v.end(), 11, student_cmp());
```

法四：使用 lambda.

Lambda
https://stackoverflow.com/questions/17711652/lower-bound-of-vector-of-pairs-with-lambda

https://cc321.ltd/2021/07/25/C-lower-bound-%E4%B8%8Eupper-bound%E5%87%BD%E6%95%B0%E7%9A%84%E4%BD%BF%E7%94%A8/

# misc

二分查找有多少种写法 https://www.zhihu.com/question/36132386

像网线主管、矩形分割这种，不能直接用 lower_bound()，因为不是每个下标都有对应的值。

可能得自己实现 iterator（那还不如自己实现 lower_bound()），或者可能用到 C++20 的 ranges.

# 例题

例：266 和为给定数：给出若干个整数，询问其中是否有一对数的和等于给定的数。

```cpp
    #include <cstdio>
    #include <algorithm>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        long a[n];
        for (int i = 0; i < n; i++) {
            scanf("%ld", &a[i]);
        }
        long m;
        scanf("%ld", &m);

        stable_sort(a, a + n);

        for (int i = 0; i < n - 1; i++) {
            long k = m - a[i];
            if (k < a[i]) {
                break;
            }
            long *p = lower_bound(a + i + 1, a + n, k);
            long j = p - a;
            if (j < n && j >= i + 1 && a[j] == k) {
                printf("%ld %ld\n", a[i], a[j]);
            }
        }
        return 0;
    }
```
