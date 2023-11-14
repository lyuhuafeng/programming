#include <cstdio>

int n, T;
int a[30];
int c[30]; // c[i]==0:未使用; 1:使用
int cnt = 0;

void dfs(int sum, int cur, int total) {
    if (sum == T && total > 0 && c[cur] == 1) {
        for (int i = cur; i <= n - 1; i++) {
            if (c[i] == 1) {
                printf("%d ", a[i]);
            }
        }
        printf("\n");
        cnt++;
    }

    // 先判断是否已到尽头，是否还能往下递归
    if (cur == 0) { return; }
    // 两个选择之一：不使用 cur-1
    c[cur - 1] = 0;
    dfs(sum, cur - 1, total);
    // 两个选择之二：使用 cur-1
    c[cur - 1] = 1;
    dfs(sum + a[cur - 1], cur - 1, total + 1);
    c[cur - 1] = 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &T);

    // cur 在范围之外。dfs()的首次调用，选择是否使用第一个(cur=n-1)元素。 
    dfs(0, n, 0);
    printf("%d", cnt);

    return 0;
}
