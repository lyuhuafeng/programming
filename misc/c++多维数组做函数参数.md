# c++ 二维数组作为函数参数

以二维数组为例

# fixed-length array，每个维度的大小也是数组类型的一部分

- 法一，参数数组中，指定所有维度的大小
  - `f1()` 的 `a` 需要指定两个维度大小

```cpp
    // 声明 a，并给 a 赋值。多种方式均可。
    int a[3][5] = {{2, 9, 3, 1, 5}, {6, 5, 6, 5, 0}, {0, 3, 4, 0, 1}};
    // 或
    int a[3][5];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    // 或
    const int M = 3, N = 5;
    int a[M][N] = {{2, 9, 3, 1, 5}, {6, 5, 6, 5, 0}, {0, 3, 4, 0, 1}};
    // 或
    int a[][N] = {{2, 9, 3, 1, 5}, {6, 5, 6, 5, 0}, {0, 3, 4, 0, 1}};

    // 法一，a[3][5] 指定两个维度的大小
    void f1(int a[3][5]) {
        a[0][0] = 7; // 改动会影响到 f1() 之外
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 5; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }

    // 调用方法
    f1(a);
```

- 法二，参数数组中，第一维可以省略，其他维要指定大小。但第一维大小需用单独参数传递。
  - `f2()`、`f3()` 的参数 `a[][5]`，第一维大小省略，只指定了第二维的大小。但还有 `rows` 参数，用于指定第一维的大小。

```cpp
    // 声明 a，并给 a 赋值，多种方式，完全同上，略

    // 法二，参数 `a[][5]`，第一维大小省略，只指定了第二维的大小。但还有 `rows` 参数，用于指定第一维的大小。
    // f2()、f3() 代码完全相同。
    void f2(int a[][5], int rows) {...}
    void f3(int (*a)[5], int rows) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < 5; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }

    // 调用方法
    f2(a, 3);
    f3(a, 3);
```

- 法三，用 template（模板参数），参数数组不需指定任何维度的大小。但所有维度大小需用参数传递。

```cpp
    // 声明 a，并给 a 赋值，略

    // 法三，用 template，a 不需指定任何维度的大小，但所有维度大小需用参数传递。
    // 不能用于 variable-length array。
    template <typename T>
    void f5(T a, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    // 调用
    f5(a, 3, 5);
```

另一种类似写法：
```cpp
    // 不能用于 variable-length array。
    template <size_t rows, size_t cols>
    void pr(int (&a)[rows][cols]) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    // 调用
    pr(a);
```

数据类型、二维数组大小，都用模版。调用时不需指定各维度的大小。
```cpp
    // 不能用于 variable-length array。
    template<typename T, int M, int N>
    T f_sum(const T (&a)[M][N]) {
        T s = 0;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                s += a[i][j] * a[i][j];
        return s;
    }
    // 调用
	double a[][2] = {{ 1.11, 2.24 }, { 3.38, 4.40 }};
	double ans = f_sum(a);

    // 错误调用方式：不能用于 variable-length array。
    int rows = 2, cols = 2; // 若改成 const int 就正确了
	double a[rows][cols];
    a[0][0] = 1.11, a[0][1] = 2.24, a[1][0] = 3.38, a[1][1] = 4.40;
    double ans = f_sum(a); // 编译错误

```

法三是最佳。若有多个维度相同（例如，都是二维）但大小不同（例如，`a[5][3]`，`b[4][9]`）的数组，法一法二都需要给 a、b 单独定义函数，因为 a、b 的数据类型不同。而法三可适应不同大小的数组。(若维度不同，其实参数 a 也可以适应，但需要传递每个维度大小的参数个数不同，还是得定义不同的函数。)

<font color="red">但 `f5()` 和 `pr()` 以及 `f_sum()` 的参数，仍然不能用 variable-length array。</font>

```cpp
    // 错误：不能用于 variable-length array
    int n = 3, m = 4;
    int c[n][m]; // variable-length array
    f5(c, n, m);

    // 错误信息：
    //   模板参数不能引用变长数组类型C/C++(1660)
    //   candidate template ignored: substitution failure:
    //   variably modified type 'int (*)[m]' cannot be used as a template argument
```


# variable-length array 作为函数参数

传指针而不是 array。也适用于 fixed-length array。

```cpp
    // 声明 a，并给 a 赋值，略

    void f4(int *a, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printf("%d ", a[i * cols + j]); // 或 *(a + i * cols + j)
            }
            printf("\n");
        }
    }

    // 调用方法，下面四种都可以。
    f4(&a[0][0], 3, 5);
    f4((int *) a, 3, 5);
    f4(a[0], 3, 5);
    f4((int *) a[0], 3, 5);
```

# 不用 array，改用 vector

就是声明数组 `vector<vector<int>> c(n, vector<int>(m))` 有点麻烦。

```cpp
    void g1(vector<vector<int>> &a) {
        int rows = a.size(), cols = a[0].size();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }

    // 调用
    int n = 3, m = 5;
    vector<vector<int>> c(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &c[i][j]);
        }
    }
    g1(c);
```

# c99

注意 `print()` 和 `print2()` 的参数，`rows` 和 `cols` 要在 `a[][cols]` 和 `a[rows][cols]` 之前。

此法可适用于 fixed-length array 和 variable-length array。

```c
    void print(int rows, int cols, int a[][cols]) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    void print2(int rows, int cols, int a[rows][cols]) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }

    int main() {
        const int N = 4;
        int arr[][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}; // fixed-length array
        int m = sizeof arr / sizeof arr[0];
        print(m, N, arr);
        print2(m, N, arr);

        int height = 3, width = 5;
        int c[height][width]; // variable-length array
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                scanf("%d", &c[i][j]);
            }
        }
        print(height, width, c);
        print2(height, width, c);
        return 0;
    }
```

https://stackoverflow.com/questions/14548753/passing-a-multidimensional-variable-length-array-to-a-function

VLA with reversed arguments, forward parameter declaration (GNU C extension)

```c
    void foo(int width; int arr[][width], int width) {
        arr[x][y]=5;
    }
`

C++ with VLA (GNU C++ extension, terribly ugly)

```cpp
    void foo(int width, int* ptr) {
        typedef int arrtype[][width];
        arrtype& arr = *reinterpret_cast<arrtype*>(ptr);
        arr[x][y] = 5;
    }
```

改进：
- `auto arr = reinterpret_cast<int (&)[][width]>(ptr);`
- `using arrtype = int[][width]` 比 `typedef int arrtype[][width]` 更好看些。

# 躺平

数组声明为 global 的，也不用管是 fixed 还是 variable-length 的，也不用传递了。

