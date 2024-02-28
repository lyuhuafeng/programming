# `luogu p2629.` 好消息、坏消息

- [`luogu p2629`](https://www.luogu.com.cn/problem/P2629)
- [`l5, u9, ex3`](https://oj.youdao.com/course/37/278/1#/1/14205)

若无「倒叙」，则算前缀和 `ps[]`，看 `ps[1-n]` 里最小的是否小于 0。

有「倒叙」后，序列扩展一倍，用来模拟环。

遍历每个可能的 k，在范围为 n 的窗口内取前缀和的最小值。因此时的前缀和不是从第 1 个元素算起的，还要减去窗口左界对应的前缀和。

我的成功代码

```cpp
    #include <queue>
    #include <cstdio>
    using namespace std;
    
    int main() {
        int n;
        scanf("%d", &n);
        long long a[2 * n + 1]; // 下标1~2*n-1有用。下标2*n无用，为代码简单。
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            a[i + n] = a[i];
        }
        a[0] = 0;
        for (int i = 1; i <= 2 * n - 1; i++) {
            a[i] += a[i - 1];
        } // 以上四行：算前缀和，复用a[] 空间，省内存
    
        deque<int> q;
        int cnt = 0;
        for (int i = 1; i <= 2 * n - 1; i++) {
            while (!q.empty() && q.front() + n - 1 < i) {
                q.pop_front();
            }
            while (!q.empty() && a[q.back()] > a[i]) {
                q.pop_back();
            }
            q.push_back(i);
            if (i >= n) {
                int k = i - n + 1;
                long long minv = a[q.front()] - a[k - 1];
                if (minv >= 0) {
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
        return 0;
    }
```

Turing 标程：

```cpp
    #include <queue>
    #include <cstdio>
    using namespace std;
    
    const int maxn = 1e6 + 5;
    int n, ans;
    long long a[2 * maxn], sum[2 * maxn];
    deque<int> q;
    
    int main() {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            a[i + n] = a[i];
        } // 断环为链，存2*n个数
        for (int i = 1; i <= 2 * n - 1; i++) { // 处理1到2n-1个前缀和
            sum[i] = sum[i - 1] + a[i];
        }
        for (int i = 1; i <= 2 * n - 1; i++) {
            // 枚举可能的方案，i为当前收到的最后一条消息
            while (!q.empty() && sum[q.back()] >= sum[i]) {
                q.pop_back();
            }
            q.push_back(i);
            // 先处理队尾新元素入队
            if (i >= n) { //消息数量要达到n，否则不足以判断
                while (!q.empty() && q.front() <= i - n) {
                    q.pop_front();
                } // 丢掉n条之前的废消息
                if (sum[q.front()] - sum[i - n] >= 0) {
                    ans++;
                }
                // 求最小区同和井判断方案是否合法
            }
        }
        printf("%d\n", ans);
        return 0;
    }
```

与我的代码的主要区别：

我先处理 q 头，再处理 q 尾；标程顺序相反。经思考，顺序无关。



