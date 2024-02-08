#include <cstdio>
#include <vector>
using namespace std;

/*
n = end - start，共移动这么多步。如果 end < start，对称一下就行，不影响结果。
改为，从起点 0 出发，经过 k 步到达终点 n。
f(k,j): 从起点 0 出发，经过 k 步，到达 j，的方案数。k-1 步时，若到达了 j 的左边或右边，则 k 步时可到达 j。故
f(k,j) = f(k-1,j-1) + f(k-1,j+1)

从 0 出发，往左，设最远可到位置 -l。l + l + n ≤ k，l ≤ (k-n)/2，l = (k-n)/2，向下取整。
往右，最远可到达位置 r。r + (r-n) ≤ k，r ≤ (k+n)/2。

为使下标不小于 0，
最左：-l，起点：0，终点：n，最右：r，结果：f(k,n)
都加 l，变为：0, l, n+l, r+l, f(k,n+l)
*/

    int numberOfWays(int startPos, int endPos, int k) {
        const long long M = 1e9 + 7;

        int n = abs(startPos - endPos);
        if (n > k) {
            return 0;
        }
        int l = (k - n) / 2, r = (k + n) / 2; // 都向下取整
        int f[k + 1][r + l + 1];
        // 初始化 k=0，一步不走，f(0,l)=1，f(0,i)=0。
        fill_n(&f[0][0], r + l + 1, 0);
        f[0][l] = 1;

        for (int i = 1; i <= k; i++) {
            for (int j = 0; j <= r + l; j++) {
                if (j == 0) {
                    f[i][j] = f[i-1][j+1];
                } else if (j == r + l) {
                    f[i][j] = f[i-1][j-1];
                } else {
                    f[i][j] = (f[i-1][j-1] + f[i-1][j+1]) % M;
                }
            }
        }
        int ans = f[k][l + n];
        return ans;
    }

int main() {
    int start = 1, end = 2, k = 3;
    int ans = numberOfWays(start, end, k);
    printf("%d\n", ans);
    return 0;
}