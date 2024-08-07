#include <cstdio>
#include <algorithm> // max(), fill_n()
using namespace std;

void display(int i, int j, int dp[], int W) {
    printf("i:%2d, j:%3d | ", i, j);
    for (int k = 1; k <= W; k++) {
        printf("%4d", dp[k]);
    }
    printf("\n");
}

int opt1(int n, int w[], int v[], int W) {
    int dp[W + 1];
    fill_n(dp, W + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = w[i]; j <= W; j++) { // 正序遍历
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            // // 或下面这种方法
            // int t = dp[j - w[i]] + v[i];
            // if (t > dp[j]) {
            //     dp[j] = t;
            // }
            // display(i, j, dp, W);
        }
    }
    return dp[W];
}

int main() {
    int n;  // 共多少件物品
    int W;  // 购物车容量
    scanf("%d%d", &n, &W);
    
    int w[n + 1], v[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }

    int max_value = opt1(n, w, v, W);

    printf("max value: %d\n", max_value);
    return 0;
}