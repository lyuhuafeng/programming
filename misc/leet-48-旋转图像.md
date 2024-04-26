# [`48.` 旋转图像](https://leetcode.cn/problems/rotate-image)

`n × n` 的二维矩阵，顺时针旋转 90 度。「原地」旋转，也就是要直接修改输入的二维矩阵，不能借助另一个矩阵。

先看「新建」矩阵的情况，比较好理解。代码见下，关键一句是 `t[i][j] = r[n - 1 - j][i]`。注意，下标从 0 开始或从 1 开始，代码只差一个符号，`n-1-j` 或 `n+1-j`。

```cpp
// 下标从 0 开始
    char r[n][n], t[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = r[n - 1 - j][i]; // 注意 n-1-j
        }
    }

// 下标从 1 开始
    char r[n + 1][n + 1], t[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            t[i][j] = r[n + 1 - j][i]; // 注意 n+1-j
        }
    }
```

再看「原地」旋转的情况。几种解法，都是下标从 0 开始，用 `n-1-j`。法一、法二的循环条件不同，但核心的五个赋值语句完全一样；法三在法二的基础上，把核心的五次赋值语句用一个循环处理。

法一
```cpp
    // 完全独立的解法，与官方解法二思路相同，但更可读
    void rotate(vector<vector<int>>& m) {
        int n = m.size(); // n*n
        int k1 = 0, k2 = 0;
        if (n % 2 == 0) {
            k1 = n / 2 - 1; k2 = k1;
        } else {
            k1 = n / 2; k2 = k1 - 1;
        }
        n--; // 这里减 1，下面的 n-1 就可以都用 n，代码简单点
        for (int i = 0; i <= k1; i++) {
            for (int j = 0; j <= k2; j++) {
                int t = m[n - j][i];
                m[n - j][i] = m[n - i][n - j];
                m[n - i][n - j] = m[j][n - i];
                m[j][n - i] = m[i][j];
                m[i][j] = t;
            }
        }
    }
```

法二
```cpp
    void rotate(vector<vector<int>>& m) {
        int n = m.size(); // n*n
        // 从外围向内围进行, p 是当考虑的小矩阵距离原矩阵的边距
        for (int p = 0; 2 * p <= n; p++) {
            // 考虑红色上边框上的每个元素
            // 从 [p, p] 到 [p, n-1-p] 依次开始转
            // 注意避开行尾 (即 j 严格小于 n-1-p)
            for (int i = p, j = p; j < n - 1 - p; j++) {
                // 把元素 [i,j] 连续旋转 4 次
                int t = m[n - 1 - j][i];
                m[n - 1 - j][i] = m[n - 1 - i][n - 1 - j];
                m[n - 1 - i][n - 1 - j] = m[j][n - 1 - i];
                m[j][n - 1 - i] = m[i][j];
                m[i][j] = t;
            }
        }
    }
```

法三
```cpp
    void rotate(vector<vector<int>>& m) {
        int n = m.size(); // n*n
        // 从外围向内围进行, p 是当考虑的小矩阵距离原矩阵的边距
        for (int p = 0; 2 * p <= n; p++) {
            // 考虑红色上边框上的每个元素
            // 从 [p, p] 到 [p, n-1-p] 依次开始转
            // 注意避开行尾 (即 j 严格小于 n-1-p)
            for (int i = p, j = p; j < n - 1 - p; j++) {
                // 把元素 [i,j] 连续旋转 4 次
                for (int x = i, y = j, t = m[i][j], k = 0; k < 4; k++) {
                    int tx = y, ty = n - 1 - x;
                    swap(t, m[tx][ty]);
                    x = tx, y = ty;
                }
            }
        }
    }
```

