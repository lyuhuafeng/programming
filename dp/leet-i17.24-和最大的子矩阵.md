# [面试题 17.24 和最大的子矩阵](https://leetcode.cn/problems/max-submatrix-lcci/)

把二维问题转成一维问题，b[]: 对每个 (i,j)，求第 i 行到第 j 行的累加值。

然后在一维序列 b[] 上求「子数组和的最大值」

代码待美化：

```cpp
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int sum; // 相当于dp[i],dp_i
        int max_sum = INT_MIN;
        int besti, bestj; // 暂时记录左上角，相当于begin
        vector<int> ans(4); // 保存最大子矩阵的左上角和右下角的行列坐标

        for (int i = 0; i < n; i++){      // 以i为上边，从上而下扫描
            vector<int> b(m, 0);  // 记录当前i~j行组成大矩阵的每一列的和，将二维转化为一维
            for(int j = i; j < n; j++){     // 子矩阵的下边，从i到n-1，不断增加子矩阵的高
                 // 一下就相当于求一次最大子序列和
                sum = 0; // 从头开始求dp
                for(int k=0; k<m; k++) {
                    b[k] += matrix[j][k];   
                    if (sum > 0) {
                        sum += b[k];
                    } else {
                        sum = b[k];
                        besti=i, bestj=k; // 自立门户，暂时保存其左上角
                    }
                    if (sum > max_sum) {
                        max_sum = sum;
                        ans = {besti, bestj, j, k}; // 更新答案
                    }
                }
            }
        }
        return ans;
    }
```
