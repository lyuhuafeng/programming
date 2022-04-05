# 计数排序 counting sort

## 关键点
如果数组中共有 `i` 个元素小于等于 `x`，那么 `x` 的排序后的下标为 `i` （下标从 `0` 开始）。


## 算法步骤

待排序数据都是大于等于 0 的整数。
* 原始数据，未排序的：`a[]` 数组
* 排好序的数据，放在 `b[]` 数组中
* 辅助数组，用来计数的，`count[]` 数组。

步骤：

1. 找出待排序数的最大值 `max`。所有数的范围是 `[0, max]` 闭区间。

2. 辅助数组，大小为 `max + 1`，并且初始化为 `0`，用来记录每个数出现了多少次。
```cpp
    int count[max + 1];
```
`count[i]` 存放数 `i` 出现的次数。例如，若 `4` 出现了 `2` 次，则 `count[4] = 2`。

3. 累加（计数算法核心）

```cpp
    count[i] += count[i - 1];
```

* `count[i]` 表示：`i` 以及比它小的数总共出现了多少次。
* `count[i - 1]` 表示：`i - 1` 及比它小的数共出现了多少次
* 所以，`i` 出现了 `count[i] - count[i - 1]` 次。排序后，`i` 的下标，从 `count[i]` 开始倒数，到 `count[i - 1] + 1` 止。在代码里，是倒着填充的。
* (还可推出，比 `i + 1` 小的数共出现了 `count[i]` 次，所以 `i + 1` 是第 `count[i] + 1` 个数。在下标从 `0` 开始的情况下，(第一个出现的) `i + 1` 的下标是 `count[i]`。排序后，`i + 1` 的下标应该是 `count[i]`，也就是 `b[count[i] + 1] = i + 1`。不过下面的代码并未用到这一点。)

5. 倒序，在 `count[]` 数组中找每个数的下标。

每确定一个数 `a[i]` 的最终位置后，将 `count[]` 减 `1`。

Why? 若该数出现多次，每将一个 `a[i]` 放入 `b[]` 数组时，都将 `count[a[i]]` 值减 `1`。这样，当下个等于 `a[i]` 的待排序元素出现时，在排序过的 `b[]` 数组中，次数会被放到 `b[i]` 的前一个位置上。这样可以保证排序的稳定性。

## 代码
```cpp

#include <iostream>
using namespace std;

void display(int[], int, string);

void count_sort(int a[], int size) {
  // a[]: 待排序
  // count[]: 计数用;
  // b[]: 排好序后
  int b[100];
  int count[100];

  // 找出最大值 maxn
  int maxn = a[0];
  for (int i = 1; i < size; i++) {
    if (maxn < a[i]) {
      maxn = a[i];
    }
  }

  // 初始化 count[], 下标范围 [0, maxn] 闭区间, 共 maxn + 1 个元素。
  for (int i = 0; i <= maxn; i++) {
    count[i] = 0;
  }

  // 统计每个元素的出现次数. count[i] 就是元素 i 的出现次数
  for (int i = 0; i < size; i++) {
    count[a[i]]++;
  }
  display(count, maxn, "count");

  // 累计计数
  // count[i] 是 <=i 的元素的总出现次数
  for (int i = 1; i <= maxn; i++) {
    count[i] += count[i - 1];
  }
  display(count, maxn, "count");

  // 初始化 b[] 各元素为 0。
  // 只是为了打印中间过程；实际上没必要。
  for (int i = size - 1; i >= 0; i--) {
      b[i] = 0;
  }
  display(b, size, "b");

  // 将 a[] 各元素倒序依次放入 b[] 中合适位置
  for (int i = size - 1; i >= 0; i--) {
    b[count[a[i]] - 1] = a[i];
    display(b, size, "b");
    count[a[i]]--;
  }

  for (int i = 0; i < size; i++) {
    a[i] = b[i];
  }
}

void display(int array[], int size, string s) {
  cout << s << ": ";
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main() {
  int a[] = {4, 2, 2, 8, 3, 3, 1};
  int n = sizeof a / sizeof(int);
  display(a, n, "a");
  count_sort(a, n);
  display(a, n, "a");
}
```
输出：
```
a: 4 2 2 8 3 3 1
count: 0 1 2 2 1 0 0 0
count: 0 1 3 5 6 6 6 6
b: 0 0 0 0 0 0 0
b: 1 0 0 0 0 0 0
b: 1 0 0 0 3 0 0
b: 1 0 0 3 3 0 0
b: 1 0 0 3 3 0 8
b: 1 0 2 3 3 0 8
b: 1 2 2 3 3 0 8
b: 1 2 2 3 3 4 8
a: 1 2 2 3 3 4 8
```
