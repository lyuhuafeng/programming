# 石头上的香蕉（智慧杯第四届，第三题）

大嘴猴在森林里发现了一个神奇的排成一排的巨石阵。每晚在每块巨石上都会出现若干根好吃的香蕉，当太阳升起时，所有香蕉就会消失。

大嘴猴发现一个规律，如果它拿走相邻两块巨石上的香蕉，那么巨石阵很久都不会出产香蕉。

大嘴猴想知道，在每晚都能吃到香蕉的情況下，一晚能拿走的最多的香蕉数量。


# 分析

动态规划典型例题。注意，不相邻。

`dp[i]`: 石头 `[0 .. i]` 最多能拿走多少香蕉。

代码：

```cpp
#include <cstdio>
#include <algorithm> // max()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int bananas[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bananas[i]);
    }
    if (n == 1) {
        printf("%d\n", bananas[0]);
        return 0;
    }

    int stones[n];
    stones[0] = bananas[0];
    stones[1] = max(bananas[0], bananas[1]);
    for (int i = 2; i < n; i++) {
        stones[i] = max(stones[i - 2] + bananas[i], stones[i - 1]);
    }
    printf("%d\n", stones[n - 1]);

    return 0;
}
```

