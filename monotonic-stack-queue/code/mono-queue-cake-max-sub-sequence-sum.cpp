#include <cstdio>
#include <deque>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int sum[n + 1];
    sum[0] = 0;
    int tmp;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tmp);
        sum[i] = sum[i - 1] + tmp; // 直接算出前缀和，不保留原值
    }
    int ans = 0;
    deque<int> q; // 单调上升，存序号
    q.push_back(0); // 为了使 i=1 时的值能统计进ans
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() + m < i) {
            // 要找 i-1 ~ i-(m-1) 范围内最小的，所以应满足 队头 + m 
            q.pop_front();
        }
        if (!q.empty()) {
            ans = max(ans, sum[i] - sum[q.front()]);
        }
        while (!q.empty() && sum[i] < sum[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}