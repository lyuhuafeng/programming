
必须提供：
- hash function
  - 重载 `operator()` 的 class/struct
  - 用 a specializations of the template `std::hash`
- comparison function for equality
  - 重载 `operator()` 的 class/struct
  - 用 a specialization of `std::equal` <font color="red">to check later</font>
  - 自定义类型中，重载 `operator==`（最简单）

## 法一

- 自定义类型（struct person），重载 `operator==`，用来比较两个 key 是否相等。
- 类型，多了 `unordered_map<KeyType, ValueType, hash_func> um`，多了个 hash_func 类型，对应 hash 函数。hash_func 是个 class 或 struct，必须重载 `operator()` 操作符。

代码

```cpp
    struct person {
        string first, last; // First and last names
        person(string f, string l) { first = f, last = l; }
    
        bool operator==(const person& p) const {
            return first == p.first && last == p.last;
        }
    };
    
    class my_hash_func {
    public:
        // 法一：简单用名字长度作为 hash 值
        // 法二：用 std::hash<> 计算 hash 值
        size_t operator()(const person& p) const {
            // return p.first.length() + p.last.length(); // 法一
            return hash<string>()(p.first) ^ (hash<string>()(p.last) << 1); // 法二
        }
    };
    
    // 调用
    unordered_map<person, int, my_hash_func> um;
    person p1("huafeng", "lu");
    person p2 = {"igor", "lyu"};
    um[p1] = 100;
    um.insert({p2, 100});
```

另一个例子

```cpp
    struct point {
        int x, y;
        point(int x, int y) : x(x), y(y) {}
        bool operator==(const point& other) const {
            return x == other.x && y == other.y;
        }
    };
    
    struct point_hasher {
        size_t operator()(const point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };

    unordered_map<point, int, point_hasher> m;
```

## 二、或把 hash_func 定义在 point 类型中，也很合理：

```cpp
    struct point {
        int x, y;
        point(int x, int y) : x(x), y(y) {}
        bool operator==(const point& other) const { ... }

        struct point_hasher {
            size_t operator()(const point& p) const {
                return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
            }
        };
    };

    unordered_map<point, int, point::point_hasher> m;
```

## 三、用「specializations of the template std::hash」

这样的 specialization，就是自定义的 `std::hash<person>`。

std::hash is not actually a struct, but a template (specialization) for a struct. So it isn't an implementation -- it will be turned into an implementation when the compiler needs it. Templates should always go into header files. 

```cpp
    struct person {
        string first, last; // First and last names
        person(string f, string l) { first = f, last = l; }

        bool operator==(const person& p) const {
            return first == p.first && last == p.last;
        }
    };

    template<>
    struct hash<person> {
        size_t operator()(const person& p) const {
            return hash<string>()(p.first) ^ (hash<string>()(p.last) << 1);
        }
    };

	unordered_map<person, int> um; // 不用指定 hash_func 了
```

## 四、hash 和 equality 都用 lambda

- 自定义类型中不重载 `operator==`
- hash 和 equal 用 lambda 实现，作为参数传入

代码：

```cpp
    class my_node {
    public:
        int a, b, c;
        my_node(vector<int> v) { a = v[0]; b = v[1]; c = v[2]; }
    };

    auto hash_lambda = [](const my_node& n) {
        size_t res = 17;
        res = res * 31 + hash<int>()(n.a);
        res = res * 31 + hash<int>()(n.b);
        res = res * 31 + hash<int>()(n.c);
        return res;
    };
    auto equal_lambda = [](const my_node& n1, const my_node& n2) {
    	return n1.a == n2.a && n1.b == n2.b && n1.c == n2.c;
    };
    unordered_map<my_node, int, decltype(hash_lambda), decltype(equal_lambda)> m(8, hash_lambda, equal_lambda);

    vector<int> v {3, 8, 9};
    m[my_node(v)] = 0;
```
