#include <algorithm>
#include <cstdio>
using namespace std;

int n, m, a[201], b[20], visit[105], s1[10050], s2[100501], t;

void dfs(int cnt, int pos, int sum1, int sum2) {
    if (cnt == m) {
        s1[++t] = sum1;
        s2[t] = sum2;
        return;
    }
    if (n - pos + 1 < m - cnt) return;
    dfs(cnt + 1, pos + 1, sum1 + a[pos], sum2 + b[pos]);
    dfs(cnt, pos + 1, sum1, sum2);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    dfs(0, 1, 0, 0);
    sort(s1 + 1, s1 + t + 1);
    sort(s2 + 1, s2 + t + 1);
    int i = 1, j = 1;
    while (i <= t && j <= t) {
        if (s1[i] == s2[j]) {
            printf("%d", s1[i]);
            return 0;
        }
        if (s1[1] < s2[j]) i++;
        else j++;
    }
    printf("IMPOSSIBLE");
    return 0;
}
