#include <cstdio>
using namespace std;

// ac 2024.10.01 by igor

int n, m;
int a[10005], nums[10005];
bool found;
int cnt = 0;

void dfs(int now) {
    if (found == true) {
        return;
    }
    if (now > n) {
        cnt++;
        if (cnt == m + 1) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", a[j]);
            }
            found = true;
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt == 0) {
            i = a[now];
        }
        if (nums[i] == 0) {
            nums[i] = 1;
            a[now] = i;
            dfs(now + 1);
            nums[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dfs(1);
    
    return 0;
}