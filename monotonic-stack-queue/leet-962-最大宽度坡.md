# [962. 最大宽度坡](https://leetcode.cn/problems/maximum-width-ramp/) 

第一眼没仔细看，以为是简单的 next greater 模板题，其实不是！它定义的「坡」的两个端点形成的区间，不要求是单调递增的！其实类似 121。

# 法一

2024.05.06 ac

```cpp
    int maxWidthRamp(vector<int>& nums) {
        vector<pair<int, int>> v; // pair<value, index>
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }
        stable_sort(v.begin(), v.end()); // 按 value 排序。缺省按 first 排序，恰好
        // 按 value 排序后，对任何一个元素，其对应的坡长度是 my_idx - min_idx_so_far
        int min_idx = INT_MAX, max_width = 0;
        for (auto e : v) {
            min_idx = min(min_idx, e.second);
            max_width = max(max_width, e.second - min_idx);
        }
        return max_width;
    }
```

发现，排序后，其实跟「121. 买卖股票最佳时机 I」是一样的。排序后，元素的大小关系已经正确了，然后将下标作为股票的价格，求最大差价。参考 [121 的题解](leet-121-买卖股票最佳时机.md)。

# 法二，二分搜索

2024.05.06 ac

基本思路：对第 i 个元素，把值 >= i.value 的元素，按「下标逆序」排好序，然后二分找。例如，

```cpp
    value: 6 0 8 2 1 5
    index: 0 1 2 3 4 5
```
以第 1 个元素（值为 0）为例，它之后（下标大于它）、且值 >= 它的元素，按索引逆序排，是 (5,5) (1,4) (2,3) (8,2)。在这个序列里，找「第一个值 >= 它」的元素，就可以跟它组成一个「坡」。为什么「第一个」就可以？因为是按下标逆序排列的，越靠前的，下标越大，离「它」越远，对应「坡」也越长。这也是我们要逆序排列的原因。要是按正序排列，找「最后一个」，就麻烦些。

但这个序列的「值」不是单调的，无法二分查找。再一想，(5,5) 之后的两项，值分别是 1 和 2，都比 5 小。如果 5 不被选中（也就是说，5 不满足「>= 它」），则比 5 更小的 1 和 2 更无法满足「>= 它」，所以比 5 小的各项其实是可以不放在序列中的。序列变成 (5,5) (8,2)，各项依次增大，满足单调性，就可以用二分搜索找「第一个值 >= 它」的元素了。

实际代码中，逆序遍历 i，在比 i 大的各下标中，找对应的 j。逆序遍历 i，正好可以同时逆序生成「序列」。

代码：[leet-962-max-ramp-width-sol2.cpp](code/leet-962-max-ramp-width-sol2.cpp)。<font color="red">to do: 二分搜索用 lower_bound() </font>

```cpp
    // 二分搜索，找第一个「值 >= key」的元素
    int bsearch(const vector<pair<int, int>> &v, int key) {
        int l = 0, r = v.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (v[m].first >= key) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> v; // pair<value, index>，「下标逆序」的元素序列
        v.push_back({nums[n - 1], n - 1});
        int max_width = 0;
        for (int i = n - 2; i >= 0; i--) { // 逆序遍历 i，也方便逆序放入元素序列
            int idx = bsearch(v, nums[i]); // 在「下标逆序」序列中，到第一个「值 >= 当前值」的元素
            if (idx < v.size()) { // 找到：该元素的下标 j，与当前元素下标 i 构成一个「坡」。该元素自身不用放入「序列」中。
                int j = v[idx].second;
                max_width = max(max_width, j - i);
            } else { // 没找到：当前元素值比序列中所有元素都大。将其放入「序列」中。
                v.push_back({nums[i], i});
            }
        }
        return max_width;
    }
```

法二中，「下标逆序」序列，处理过程中感觉有点像单调栈。仔细一想，其实不是。单调栈的重要特征，是「新来的都入栈，为此不惜弹出栈顶若干元素」；本法中的处理，是「已入序列的一直在里面，为此不惜拒绝新来的入栈」。

法三