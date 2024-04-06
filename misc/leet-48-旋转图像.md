# [`48.` 旋转图像](https://leetcode.cn/problems/rotate-image)

法一
```cpp
    // 完全独立的解法，与官方解法二思路相同，但更可读
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(); // n*n
        int k1 = 0, k2 = 0;
        if (n % 2 == 0) {
            k1 = n / 2 - 1; k2 = k1;
        } else {
            k1 = n / 2; k2 = k1 - 1;
        }
        n--;
        for (int i = 0; i <= k1; i++) {
            for (int j = 0; j <= k2; j++) {
                int t = matrix[n - j][i];
                matrix[n - j][i] = matrix[n - i][n - j];
                matrix[n - i][n - j] = matrix[j][n - i];
                matrix[j][n - i] = matrix[i][j];
                matrix[i][j] = t;
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

