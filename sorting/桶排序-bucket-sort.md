# 桶排序 bucket sort, bin sort

最适用于数据在某个范围内均匀分布的情况，此时耗时 `O(n)`。

- 是一种 distribution sort (排序的中间结果 distribute 在多个中间结构 intermediate structure 中，然后再 gather 起来)
- 是 radix sort 的亲戚,a cousin of radix sort in the most-to-least significant digit flavor.
- a generalization of pigeonhole sort that allows multiple keys per bucket
- 若 bucket size 为 1，则变为 counting sort
- 若只有两个 bucket，则变为 quick sort，且 pivot 值为 middle value
- Top-down implementation of radix sort is bucket sort with both the range of values and the number of buckets being a power of 2 or the radix of the numbers that we are going to sort

步骤。注意两个重点步骤是 scatter 和 gather。

- Set up an array of initially empty "buckets".
- Scatter: Go over the original array, putting each object in its bucket.
- Sort each non-empty bucket.
- Gather: Visit the buckets in order and put all elements back into the original array.

bucket 内的排序

- 每个 bucket 内的排序，传统上使用 insertion sort。<font color="green">因为：每个 bucket 内元素很少，此时 insertion sort 比其他算法都快。</font>若每个 bucket 内元素很多，就该用其他算法。
- 如果 bucket 内排序也用 bucket sort 自己，则变为 radix sort 的亲戚。
- 特别地，the case n = 2 corresponds to quicksort (although potentially with poor pivot choices).


## 代码

c++ 代码：[`bucket-sort-with-insertion.cpp`](code/bucket-sort-with-insertion.cpp)

bucket 的数量 `k` 取「约等于」待排序序列的长度 `n`。（为何？因为 `n = k` 时，时间复杂度为 `O(n)`，详见下面说明。）

若 `n` 个元素的取值范围为 `gap = maxv - minv`，自然想到每个 bucket 覆盖的范围是 `bkt_size = gap / k`，则某个元素 `val` 对应的 bucket 下标为 `bi = int((val - minv) / bkt_size)`。

<font color="brown">但，有个问题。</font>每个 bucket 的覆盖范围是个「左闭右开」的区间。这样的 `k` 个区间，`maxv` 恰好在最后一个区间的右（开）边界，恰好没被覆盖到；用上面的公式，其 bucket 的下标为 `k`，恰好超出 `[0 ... k-1]` 的范围，造成访问越界。

如何解决？
- 法一：保持 `bkt_size` 的「正常值」，但额外加一个 bucket。令 `k = n`，`bkt_size = gap / (k-1)`。这样，其实是分成了 `k-1` 个「正常」区间，以及一个额外的、只使用了左边界的第 `k` 个区间。最后这第 `k` 个区间，只包含 `maxv` 自己（或多个，若 `maxv` 值有重复），落在左边界上。这样，就解决了访问 `bkt[]` 下标越界的问题。分析时间复杂度时，实质上是 `k = n-1`。
- 法二：令 `k = n+1`，其余与法一相同。这样，分析时间复杂度时，实质上是 `k = n`，更好看些。
- 法三：保持 bucket 数量不变，但让 `bkt_size` 比「正常值」稍大一点。令 `k = n`，`bkt_size` 在 `gap / k` 的基础上乘以一个比 1 稍大一点的系数如 `1.000001`。这样，第 `k` 个 bucket（下标为 `k-1`）就能覆盖 `maxv`，消除了那个特殊的 bucket。

代码中，采用了法二，注释掉了法三。

```cpp
    // 用于给每个 bucket 排序
    void insertion_sort(vector<float>& bkt) {
        for (int i = 1; i < bkt.size(); ++i) { // 注意从 1 开始。第 0 个元素是「已排序区」的初始态。
            float t = bkt[i];
            int j = i - 1;
            while (j >= 0 && bkt[j] > t) { // 注意 bkt[j] > t 而不是「>=」，为保持稳定性。
                bkt[j + 1] = bkt[j];
                j--;
            }
            bkt[j + 1] = t;
        }
    }

    // 输入序列长度为 n，桶的数量为 k=n
    void bucket_sort(float a[], int n) {
        float minv = a[0], maxv = a[0];
        for (int i = 0; i < n; i++) {
            minv = min(minv, a[i]), maxv = max(maxv, a[i]);
        }
        float gap = maxv - minv;
        float bkt_size = gap / n;
        int k = n + 1; // bucket 数量，与待排序的 array 长度（实质）相同
        // /* 法三 */ int k = n;
        // /* 法三 */ float bkt_size = gap / k * 1.000001;

        vector<float> b[k];
        for (int i = 0; i < n; i++) {
            int bi = int((a[i] - minv) / bkt_size);
            b[bi].push_back(a[i]);
            printf("i:%d, val:%f, idx:%d\n", i, a[i], bi);
        }

        int p = 0;
        // 每个 bucket 排序后就直接放回到 a 中
        for (int i = 0; i < k; i++) {
            insertion_sort(b[i]);
            for (int j = 0; j < b[i].size(); j++) {
                a[p++] = b[i][j];
            }
        }
    }

    int main() {
        float arr[] = {0.897, 0.896999, 0.8965, 0.896, 0.884, 0.565, 0.656, 0.1234, 0.665, 0.3434};
        int n = sizeof arr / sizeof arr[0];
        bucket_sort(arr, n);
        return 0;
    }
```

## 时间复杂度

最差情况：所有元素进入同一个 bucket。

平均情况：输入是均匀分布的。
- 初始化各桶、找到最大元素值、将各元素放入桶中：`O(n)`
- 用 insertion sort 对每个桶内元素排序：`O(∑nᵢ²)` = `O(n²/k)`。<font color="red">wiki上有数学推导</font>
- gather：`O(k)`
- 总共：`O(n + n²/k + k)`。若 k 约等于 n，则为 `O(n)`。<font color="green">有点神奇，一堆 `O(nᵢ²)` 加起来，得到 `O(n)`。</font>

## 稳定性

取决于每个 bucket 的排序算法。若用 insertion sort，则整个 bucket sort 是稳定的。

## 优化

来自 wiki，<font color="red">需深入理解</font>

- 每个 bucket 里的元素，不排序就放回原数组，然后对整个数组做 insertion sort。因 insertion sort 的 run time is based on how far each element is from its final position，故比较次数比较少，而且 storing the list contiguously in memory 能更好利用 memory hierarchy。
- 若输入数据的分布已知或可估算，通常可做到选择包含常数密度 const density（而不是仅具有常数大小 const size）的桶。这样，即使不是均匀分布，也能做到 `O(n)`。
- 我们可以先设定一条大致的分界线，将数据粗略地分到 3 个桶中。分配完毕后，再将商品较多的桶继续划分为 3 个桶，直至所有桶中的元素数量大致相等。本质上是创建一棵递归树，目标是让叶节点的值尽可能平均。当然，不一定要每轮将数据划分为 3 个桶，具体划分方式可根据数据特点灵活选择。
- 如果我们提前知道商品价格的概率分布，则可以根据数据概率分布设置每个桶的价格分界线。值得注意的是，数据分布并不一定需要特意统计，也可以根据数据特点采用某种概率模型进行近似。假设商品价格服从正态分布，这样就可以合理地设定价格区间，从而将商品平均分配到各个桶中。
- reference: https://www.hello-algo.com/chapter_sorting/bucket_sort

## 变种

reference: [wikipedia](https://en.wikipedia.org/wiki/Bucket_sort), [simplelearn](https://www.simplilearn.com/tutorials/data-structure-tutorial/bucket-sort-algorithm)

- Generic bucket sort
- proxmap sort
- histogram sort
- postman's sort
- shuffle sort

## to read

- https://www.linkedin.com/advice/0/what-best-practices-bucket-sort-algorithms-skills-algorithms-x2pxf
- https://www.theknowledgeacademy.com/blog/bucket-sort/
- https://www.shiksha.com/online-courses/articles/bucket-sort-algorithm-use-and-comparison/
- https://www.coding-time.cn/lc/algorithms/sorting/bucket-sort
- https://blog.csdn.net/qq_27198345/article/details/126516234
