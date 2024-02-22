#include <cstdio>
#include <vector>
#include <algorithm> // max()
using namespace std;

// 2024.02.22 luogu ac

int dp[6000 + 1][2];

// dp[i][0]: i 自己不参加；dp[i][1]: i 参加
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
    vector<int> children[n + 1]; // 每个人的 child 列表
    int is_child[n + 1];
    fill_n(is_child, n + 1, 0); // 初始化：都不是 child

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
    } // rt 是最大的上级、整棵树的 root，唯一一个 is_child == 0 的

    happiest(rt, n, children, r);
    int ans = max(dp[rt][0], dp[rt][1]);
    printf("%d\n", ans);
    return 0;
}