#include <cstdio>
using namespace std;

int n, k, cnt;

// last: 当前可以用的数的最小值
// sum: 当前累积和
// cur: 当前已经走了几步；显然从 1 算起。
void dfs(int last, int sum, int cur) {
    if (cur == k) {
        if (sum == n) {
            cnt++;
        }
        return;
    }
    for (int i = last; sum + i * (k - cur) <= n; i++) {
        dfs(i, sum + i, cur + 1);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    dfs(1, 0, 0); // 参数：可用的最小数是 1，累积和是 0，已经走了 0 步
    printf("%d", cnt);

    return 0;
}
