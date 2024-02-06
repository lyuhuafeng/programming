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

比较两个数，或一个初始化列表(用{}括起来的)；还可提供比较函数。

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
- `<math.h>` 放在 global namespace里。

大部分函数都重载为支持多种数据类型。例如 `std::exp()`：
```cpp
  #include <cmath>
  double exp(double x);
  float exp(float x);
  long double exp(long double x);
  double exp(T x); // T为各种整数类型
```

# 取整

- int(x), (int) x: 舍去小数，向 0 取整。`-1.32 -> -1`, `-1.67 -> -1`.
- round(x): 四舍五入。`-1.32 -> -1`, `-1.67 -> -2`.
- floor(x): 向下取整
- ceil(x): 向上取整

%: 取模运算 modulo, 数学上用 mod。
7 mod 3 = 1, 7 % 3 = 1.

- 如果 a 和 b 都是正数，则 a % b 值就是 a/b 的余数 (reminder)。
- 如果 a、b 中有负数，则 a % b 值有多种定义，不同编程语言中定义也不同。

- C99 和 C++11 之前：未明确定义。
- C99 和 C++11 开始：用 truncated division (截断除法) 定义：
  - / (商) 舍去小数，向 0 取整. 保证 `a / b = -a / b`。
  - % (模) 符号与被除数相同. 保证 `商 * b + 模 = a`。

a | b | 商 `a/b` | 模 `a%b`
---- |---- | ---- | ----
7 | 3 | 2 | 1
7 | -3 | -2 | 1
-7 | 3 | -2 | -1
-7 | -3 | 2 | -1

# 绝对值

使用 std::abs() 就行，不用 std::fabs() 或 ::abs().
- std::abs() 支持各种整数和各种浮点数
- std::fabs() 在 c++11 之前只支持浮点数, c++11 之后也支持各种整数。
- ::abs() 只支持 int

# 乘方、开方、对数


# 遍历 vector 时删除元素

```cpp
    for (vector<block>::iterator it = v.begin(); it != v.end(); /* it++ */) {
        printf("%d ", *(it->vpos.begin()));
        if (it->vpos.empty()) {
            v.erase(it); // 删，则不需 it++
        } else {
            it++; // 不删，则 it++
        }
    }
```
