#include <cstdio>

int n, T;
int a[30];
int c[30]; // c[i]==0:未使用; 1:使用
int cnt = 0;

void display_result(int cur) {
        for (int i = cur; i <= n - 1; i++) {
            if (c[i] == 1) {
                printf("%d ", a[i]);
            }
        }
        printf("\n");
}
void dfs(int sum, int cur, int total) {
    if (sum == T && total > 0 && c[cur] == 1) {
        display_result(cur);
        cnt++;
        // 这里找到了一个答案，但并不 return，因为如果后面几个数和为 0，也能再次凑成 T。
        // 上面 c[cur] == 1 的目的，是为了在「不 return」的情况下，防止重复输出。
        // 因为后续若干数「不选」，仍可继续满足 sum == T && total > 0，但其实与刚找到的答案是同一组合，造成重复输出。
    }

    // 先判断是否已到尽头，是否还能往下递归
    if (cur == 0) { return; }
    // 「优先输出不包含第n个整数的」，所以，两个选择，先来「不使用的」，再来「使用的」。
    // 两个选择之一：不使用 cur-1。
    c[cur - 1] = 0;
    dfs(sum, cur - 1, total);
    // 两个选择之二：使用 cur-1
    c[cur - 1] = 1;
    dfs(sum + a[cur - 1], cur - 1, total + 1);
    // 这一步是干啥？
    c[cur - 1] = 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &T);

    // cur 为 n，在范围之外。dfs()的首次调用，选择是否使用第一个(cur=n-1)元素。 
    dfs(0, n, 0);
    printf("%d", cnt);

    return 0;
}
