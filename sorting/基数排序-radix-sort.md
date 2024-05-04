# 基数排序 radix sort

英语学习：
- base 表示单个 place value 可以有多少个数字。
- 数学上，radix 与 base 是一个意思。十六进制数 is a base-16 number system; 也可以说，has a radix of 16。
- radix 这个词来自拉丁语，意为 root。

英语学习：place value
- unit place digits
- tens place digits
- hundreds place digits

从低位到高位，依次对每一「位」排序，即可。其实是 lexical order.
- 数：右 -> 左。高位可能需要补零。属于 Least Significant Digit (LSD) Radix Sort。
- 字符串：左 -> 右。低位可能需要补「空」。属于 Most Significant Digit (MSD) Radix Sort。

对于一个 d 进制的数字，要取其第 k 位 `xₖ`，公式：

```cpp
    xₖ = ⌊x / dᵏ⁻¹⌋ % d
```

例，十进制数 `3547`，从低往高（右 -> 左），第 3 位上的数字为 `(3547 / 10³⁻¹) % 10 = 5`


对数排序的代码：[radix-sort-with-counting.cpp](code/radix-sort-with-counting.cpp)：

```cpp
    int get_max(int arr[], int n) {
        int mx = arr[0];
        for (int i = 1; i < n; i++) {
            mx = max(mx, arr[i]);
        }
        return mx;
    }

    // 对 arr[n]，根据 exp 表示的第 k 位，做 counting sort。
    // exp = 10 ^ (k-1)，k 从 1 算起。
    // 例，3547，从低往高（右 -> 左），第 3 位，对应：exp = 10^2, 这一位上的数字为 (3547 / 10^2) % 10 = 5
    void count_sort(int a[], int n, int exp) {
        int count[10];
        fill_n(count, 10, 0);

        // 统计数字出现的次数
        for (int i = 0; i < n; i++) {
            count[(a[i] / exp) % 10]++;
        }
        // 求前缀和，将「出现个数」转换为「数组索引」
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        int output[n]; // 输出数组
        for (int i = n - 1; i >= 0; i--) {
            int t = (a[i] / exp) % 10;
            output[count[t] - 1] = a[i];
            count[t]--;
        }

        for (int i = 0; i < n; i++) {
            a[i] = output[i];
        }
    }

    void radix_sort(int arr[], int n) {
        int m = get_max(arr, n);
        // 最低位 -> 最高位（右 -> 左），依次对每一位排序
        for (int exp = 1; exp <= m; exp *= 10) { // 'exp <= m' 另一种写法：'m / exp > 0'
            count_sort(arr, n, exp);
        }
    }

    int main() {
        int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
        int n = sizeof arr / sizeof arr[0];
        radix_sort(arr, n);
    }
```

时间复杂度为 `O((n+d) * k)`，其中 数据量为 n，数据为 d 进制，最大元素是 k 位数。对每一位做 counting sort 耗时 `O(n + d)`，一共 k 位，总耗时 `O((n+d) * k)`。通常，d 和 k 都较小，时间复杂度趋向 `O(n)`。

与 counting sort 相比，radix sort 适用于数值范围较大的情况，但数据必须能表示为固定位数的格式，且位数不能过大。例如，浮点数不适合 radix sort，因为其位数 k 过大，可能导致时间复杂度 `O((n+d) * k)` 远大于 `O(n²)`。

非自适应排序

不是 in-place 的，要借助长度为 n 的 output[] 数组、长度为 d 的 count[] 数组，空间复杂度为 `O(n + d)`。

稳定性：取决于给每一位排序用的算法。通常用 counting sort，是稳定的。

further reading
- [这个 purdue univ 的讲义](https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap8c.pdf) 提到了 radix exchange sort 和 direct radix sort。
