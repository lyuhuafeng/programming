#include <cstdio>
#include <vector>
#include <climits> // INT_MIN
#include <algorithm> // max()
using namespace std;

const int MAXN = 100005;
long long dp[MAXN], a[MAXN]; // a[i]: 顶点 i 的权重; dp[i]: 顶点 i 为起点的最大路径和
vector<int> v[MAXN]; // v[i]: 顶点 i 出发能达到的顶点列表

long long dfs(long long x) {
    if (dp[x] > INT_MIN) {
        return dp[x];
    }
    dp[x] = a[x];
    for (int i = 0; i < v[x].size(); i++) {
        dp[x] = max(dp[x], a[x] + dfs(v[x][i]));
    }
    return dp[x];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
    }
    long long ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dfs(i));
    }
    printf("%lld\n", ans);
    return 0;
}