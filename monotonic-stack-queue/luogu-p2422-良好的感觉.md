# `luogu p2422` 良好的感觉

- [luogu p2422](https://www.luogu.com.cn/problem/P2422)
- [l5, u7, ex3](https://oj.youdao.com/course/37/277/1#/1/14196)

每一天，人都有一个感受值 `Aᵢ`（正数）。该值越大，人感觉越舒适。人在一段时间 `[i,j]` 内的舒适程度定义为
```
    [i,j] 中最不舒服的那一天的感受值 × [i,j] 中每一天感受值的和
```
现给出连续 N 天的感受值。请问，在哪一段时间，感觉最舒适？

分析：`c = min(.) × sum(.)`。吐槽：也不知道有什么物理意义。

遍历每个 `Aᵢ`，以其作为某区间内的最小值，反过来找此区间范围，使得 `c` 最大。在 `min(.) = Aᵢ` 为固定值的情况下，要求 `sum(.)` 最大。在各元素都是正数的情况下，要求区间范围最大。

`Aᵢ` 是该区间内的最小值，则区间应该是 `(Aᵢ 的 prev greater, Aᵢ 的 next greater)` 开区间，不包括两个 greater。该区间内每个数都 `<= Aᵢ`，保证 `Aᵢ` 是最小值。

计算区间 `sum(.)` 时，用前缀和。

```
区间 (pg, ng) 之和
  -> 区间 [pg+1, ng-1] 之和
  -> 前缀和之差 ps[ng-1] – ps[pg+1-1] = ps[ng-1] – ps[pg]
```
所以，
- 若某 `Aᵢ` 无 next greater，则将其 next greater 置为 `n+1`
- 若某 `Aᵢ` 无 prev greater，则将其 prev greater 置为 `0`

为了使用前缀和算区间和，前缀和数组下标从 1 开始，所以 `a[]` 下标也从 1 开始。

可能有相同元素，所以得遍历两边。下面代码，用数组模拟栈。第一遍，正序遍历，求 prev greater；第二遍，逆序遍历，也求 prev greater，实际上是正序的 next greater。都求greater，都用递减栈。

代码，luogu ac：

```cpp
    #include <cstdio>
    #include <algorithm>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        int a[n + 1];
        long ps[n + 1]; // 前缀和
        ps[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            ps[i] = ps[i - 1] + a[i];
        }

        int st[n + 1]; // 用数组模拟栈
        int top = 0;
        int l[n + 1]; // previous greater
        for (int i = 1; i <= n; i++) {
            while (top > 0 && a[st[top]] >= a[i]) {
                top--;
            }
            l[i] = top > 0 ? st[top] : 0;
            st[++top] = i;
        }

        top = 0;
        st[0] = n + 1;
        int r[n + 1]; // next greater (逆序的 previous greater)
        for (int i = n; i >= 1; i--) {
            while (top > 0 && a[st[top]] >= a[i]) {
                top--;
            }
            r[i] = top > 0 ? st[top]: n + 1;
            st[++top] = i;
        }

        long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, a[i] * (ps[r[i] - 1] - ps[l[i]]));
        }
        printf("%lld\n", ans);
        return 0;
    }
```
