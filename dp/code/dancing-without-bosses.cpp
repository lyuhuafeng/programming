#include <cstdio>
#include <vector>
#include <algorithm> // max()
using namespace std;

int dp[6000 + 1][2];

void happiest(int i, int n, vector<int> children[], int r[]) {
    dp[i][0] = 0;
    dp[i][1] = r[i];
    for (int j : children[i]) {
        happiest(j, n, children, r);
        dp[i][0] += max(dp[j][0], dp[j][1]);
        dp[i][1] += dp[j][0];
    }
}
int main() {
    int n;
    scanf("%d", &n);
    int r[n + 1]; // 欢乐值，下标为员工编号，从 1 开始 
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }
    vector<int> children[n + 1];
    int is_child[n + 1];
    memset(is_child, 0, sizeof is_child); // 初始化：都不是 son

    for (int i = 1; i <= n - 1; i++) {
        int child, parent;
        scanf("%d%d", &child, &parent);
        children[parent].push_back(child);
        is_child[child] = 1;
    }

    int rt;
    for (int i = 1; i <= n; i++) {
        if (is_child[i] == 0) {
            rt = i;
            break;
        }
    } // rt 是最大的上级、整棵树的 root

    happiest(rt, n, children, r);
    int ans = max(dp[rt][0], dp[rt][1]);
    printf("%d\n", ans);
    return 0;
}