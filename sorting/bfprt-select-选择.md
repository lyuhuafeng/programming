# bfprt 算法

quick select 的优化。最坏情况下，仍然是 `O(n)`。

优化的是选取 pivot 的策略，尽量接近中位数，以使 partition 的结果尽量均衡。

每 5 个数分为一组，找出其中位数。如何找？用 insertion sort 排序后取中间的。为何要排序？恐怕是因为这样做比互相比较要快。这 5 个排好序，算是个 side effect。

所有这些中位数，放到一起，找其中位数（所以得名 median of medians）。如何找？调用 `bfprt_select()` 自身，找这个序列的第 `size / 2` 个数（0-indexed；若 `size` 为偶数，则 `size / 2` 对应较大的那个元素）。

注意，`partition()` 和 `bfprt_select()` 互相调用，是个 mutual recursion。为何不继续递归调用「5 个一组」这种方式？因为这样找到的是「中位数们的「近似」中位数」，而 `bfprt_select()` 找到的是「中位数们的「准确」中位数」。

时间复杂度：不失一般性，每组 5 个数，假设总共分为 `2m+1` 组，总共有 `5(2m+1) = 10m+5` 个数。按上面的方法选出的近似中位数为 `mm`，则肯定比 `mm` 大的数有 `3m+2` 个，可能比 `mm` 大的数有 `5m+2(m+1) = 7m+2` 个。则，`mm` 所处的区间为 `30-70%` 范围内。按最坏情况考虑，每次 partition 分成 `30%` 和 `70%` 两部分，每次都在 `70%` 这一侧继续递归。设耗时为 `T(n)`，则 `T(n) = T(n/5) + T(7n/10) + O(n)`。无法用 master theorem 证明。但可用数学归纳法证明 `T(n)` 是 `O(n)` 的。

为什么选 5 个一组。其他数呢？显然偶数不方便求中位数。奇数里，3 不是线性的（反证法，见下），而比 5 大的都是 `O(n)` 但常系数增大。所以 5 最佳。

3 的情况：`T(n) = T(n/3) + T(2n/3) + cn, c > 0`。若 `T(n)` 是线性的，设 `T(n) = dn`，则 `T(n) = dn/3 + 2dn/3 + cn = dn + cn`，得到 `cn = 0`，与 `c > 0` 矛盾。

理论上最佳，但实际上，众多库函数并不直接用它：
- bfprt 的常数因子比随机化 quick select 大很多
- 随机化 quick select 在实际中表现很好，很难出现导致其进入最坏情况的案例
- intro select：randomized quick select + bfprt select 的结合。先 randomized，若发现退化，则切换到 bfprt。在实际中，也可以将 bfprt 替换为 heap 法，在数据量较小时尤为高效。不过这样就没 bfprt 什么事了。

partition() 要调用 bfprt_select()，所以这种 partiton 方法没法直接用到 quick sort 中。「间接」可以吗？

代码：[`bfprt-select.cpp`](code/bfprt-select.cpp)

<font color="red">to check later</font>
- `bfprt_select(arr, pi + 1, right, k - len);` 最后为啥不是 `k` 而是 `k-len`？因为最后一个参数指的是 `[left, right]` 范围内第 `k` 个，而不是 `[0, n-1]` 范围内第 `k` 个。否则 `int mm = bfprt_select(arr, left, left + j, (j + 1) / 2);` 这句就会不太方便。跟普通 quick select 不同，要注意。
- 若不 in-place 而用额外空间，则这些 median-of-5 们不用被挪到前面。对性能会有影响吗？
- in-place 也不用都挪到前面，类似 shell sort 的做法，跳着扫描？但无法递归调用 bfprt_select() 了。

```cpp
    // 标准 insertion sort
    void insertion_sort(vector<int>& arr, int start, int n) {
        for (int i = start + 1; i < start + n; i++) {
            int t = arr[i];
            int j = i - 1;
            while (j >= start && arr[j] > t) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = t;
        }
    }

    // hoare partition scheme
    int hoare_partition(vector<int>& arr, int left, int right, int pv) {
        int i = left - 1, j = right + 1;
        while (true) {
            do { i++; } while (arr[i] < pv);
            do { j--; } while (arr[j] > pv);
            if (i >= j) return j;
            swap(arr[i], arr[j]);
        }
    }

    // 找 [left, right] 范围的第 k 个 (0-indexed)，返回下标
    // in-place 的，为了找 median-of-medians，把 median-of-5's 挪到了整个 array 的前面
    int bfprt_select(vector<int>& arr, int left, int right, int k) {
        if (left == right) { return arr[left]; }

        int j = 0;
        for (int i = left; i <= right; i += 5) {
            int size = min(5, right - i + 1);
            insertion_sort(arr, i, size);
            swap(arr[left + j], arr[i + size / 2]);
            j++;
        }
        j--; // 现在 [left ... left + j] 范围是 median-of-5's，共 j+1 个

        int mm = bfprt_select(arr, left, left + j, (j + 1) / 2);
        int pi = hoare_partition(arr, left, right, mm);
        int len = pi - left + 1;
        if (len > k) {
            return bfprt_select(arr, left, pi, k);
        } else {
            return bfprt_select(arr, pi + 1, right, k - len);
        }
    }

    vector<int> arr = {12, 3, 5, 7, 4, 19, 26};
    int k = 4; // 0-indexed
    int res = bfprt_select(arr, 0, arr.size() - 1, k);
```

# references
- https://zhuanlan.zhihu.com/p/291206708
- https://en.wikipedia.org/wiki/Median_of_medians

