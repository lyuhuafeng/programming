# 常用函数

# 交换

```cpp
    #include <algorithm> // c++98
    #include <utility>   // c++11
    std::swap(a, b);     // 各种数据类型都可以，也不用传地址
```

# 最大值、最小值

```cpp
    // 适用于任何类型
    #include <algorithm>
    std::max(), std::min()

    // 适用于 float，起源于 c99，c++11 引入的
    #include <cmath>
    std::fmax(), std::fmin()
    #include <math.h>
    ::fmax(), ::fmin()
```

比较两个数，或一个初始化列表(用 `{}` 括起来的)；还可提供比较函数。

```cpp
    int a = 10, b = 13;
    printf("%d\n", std::max(a, b));	// 输出 13

    bool abs_greater(int a, int b) {
      return std::abs(a) < std::abs(b);
    }
    int a = 10, b = -13;
    printf("%d\n", std::max(a, b, abs_greater));  // 输出 -13

    std::cout << std::min({9, 5, 2, 7}); // 输出 2
    std::cout << std::min({-9, 5, 2, -7}, abs_greater); // 输出 2
```

# 数学运算

`<cmath>` vs. `<math.h>`
- `<cmath>` 把所有名字放在了 std namespace 里，对不少函数还有重载、改进、优化，用起来更方便。
- `<math.h>` 放在 global namespace 里。

大部分函数都重载为支持多种数据类型。例如 `std::exp()`：
```cpp
    #include <cmath>
    double exp(double x);
    float exp(float x);
    long double exp(long double x);
    double exp(T x); // T为各种整数类型

    T log2(T x); // 适用于 float, double, long double 类型
    log2f(float x), log2l(long double x) // 只适用指定类型
```

# 取整

- `int(x)`, `(int) x`: 舍去小数，向 0 取整。`-1.32 -> -1`, `-1.67 -> -1`.
- `round(x)`: 四舍五入。`-1.32 -> -1`, `-1.67 -> -2`.
- `floor(x)`: 向下取整
- `ceil(x)`: 向上取整

# 绝对值

使用 `std::abs()` 就行，不用 `std::fabs()` 或 `::abs()`
- `std::abs()` 支持各种整数和各种浮点数，但返回值为 float 或 double
- `std::fabs()` 在 c++11 之前只支持浮点数, c++11 之后也支持各种整数
- `::abs()` 只支持 int

`std::abs()` 在 c++14 及以前，返回值均为 float 或 double，即使参数可能是整数类型。所以，若用 `printf("%d", std::abs(...))` 打印，一定要把 `std::abs()` 的结果显示转换成 int 或 long 或其他整数类型，否则出错。（其他函数会做类型转换，但 `printf` 很特殊，不会转换，导致出错）

# `memset()` vs. `std::fill()`

可用在整数或 bool 数组上。

```cpp
    #include <cstring>

    const int n = 100;
    int a[n];
    memset(a, 0, sizeof a);

    bool visited[n];
    memset(visited, false, sizeof visited);
```

`memset()` 初始化整数类型时，只能初始化成 `-1` 或 `0`，其他的值不要用。`1` 也不行！

初始化 bool 数组时，`true` 或 `false` 都行。bool 占地 1 byte。

但最好避免使用 `memset()`，改用 `std::fill()` 或 `std::fill_n()`，（需 `#include <algorithm>`）什么类型、什么值都可以。
