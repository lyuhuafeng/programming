# [luogu p2440. 木材加工](https://www.luogu.com.cn/problem/P2440)

also on youdao: [木材加工（L3，二分天下必得其一，例 2）](https://oj.youdao.com/course/12/54/1#/1/8254)

`N` 根原木，每根长度为 `a[i]`。要总共切成 `K` 段长度相同的小段木头，希望得到的小段越长越好。求小段的最大可能长度。

原木长度、切割成的小段长度，都是正整数，单位是厘米。

若无法得到长度至少为 `1` 厘米的小段，则输出 `0`。

## 解法

二分对象：段长度 `len`。最短 `1`，最长：最长木材长度。

段长度 `len` 从小到大，段数从大到小。用 `FFFFTTTT` 方式，找第一个 `'使段数 < k'` 的长度 `len`，则 `len-1` 就可使段数为 `k`，即为所求。

`predicate(len) == true` 的判定：段数 `< k`。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

// 2024.10.13 ac

// predicate: n:原木数量, a[]:每根原木长度, chunk_len:每个小段长度，k:最终小段数量
int wood_chunks_less_than_k(int a[], int n, int chunk_len, int k) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += a[i] / chunk_len;
    }
    return cnt < k;
}

int chunk_len_upper_bound(int k, int a[], int n) {
    int l = 1;
    int r = *max_element(a, a + n) + 1; // 加1，得到右开区间
    while (l < r) {
        int m = l + (r - l) / 2;
        if (wood_chunks_less_than_k(a, n, m, k)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int len = chunk_len_upper_bound(k, a, n) - 1; // 注意减1
    if (len < 1) {
        len = 0;
    }
    printf("%d\n", len);
    return 0;
}
```
