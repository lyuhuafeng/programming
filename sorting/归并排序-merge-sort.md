# 归并排序 merge sort

- 递归方法
- 递推（非递归）方法
  - 有意思的 merge 变种方法
- 链表的归并排序（递归方法）
- 并发
- 推广

# 递归方法

完整代码：[`merge-sort-array.cpp`](code/merge-sort-array.cpp)

```cpp
    // helper: 归并 a 数组的 [left, mid]、[mid + 1, right] 两个闭区间
    void merge_lists(int a[], int left, int mid, int right, int t[]) {
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            t[k++] = a[i] > a[j] ? a[j++] : a[i++];
        }
        while (i <= mid) {
            t[k++] = a[i++];
        }
        while (j <= right) {
            t[k++] = a[j++];
        }
        for (i = left, k = 0; i <= right; i++, k++) {
            a[i] = t[k];
        }
    }

    // merge sort: 排序 a 数组的 [left, right] 闭区间范围
    void merge_sort(int a[], int left, int right, int t[]) {
        if (left == right) {
            return;
        }
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid, t);
        merge_sort(a, mid + 1, right, t);
        merge_lists(a, left, mid, right, t);
    }
```

# 递推（非递归）方法

完整代码：[`merge-sort-array-iterative.cpp`](code/merge-sort-array-iterative.cpp)

```cpp
    // 同上
    // helper: 归并 a 数组的 [left, mid]、[mid + 1, right] 两个闭区间
    void merge_lists(int a[], int left, int mid, int right, int t[]) {
        ...
    }

    void merge_sort(int a[], int n, int t[]) {
        // cur: 当前要 merge 的子区间的「半长度」，从 1 开始，每次加倍最大不超过 n - 1，
        for (int cur = 1; cur <= n - 1; cur *= 2) {
            for (int l = 0; l < n - 1; l += 2 * cur) {
                int m = l + cur - 1;
                int r = min(l + 2 * cur - 1, n - 1);
                merge_lists(a, l, m, r, t); // [l,m] [m+1,r] 与递归法里的 merge_lists() 一样
            }
        }
    }
```

## 有意思的 merge 变种方法

出自 [`88.` 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)。合并结果还放到其中一个数组中，而不是返回一个新数组。故此，三个指针都要逆序遍历。最后 nums1 里剩的元素，自然排在 nums1 最前部，不用再处理。

```cpp
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) {
            nums1[k--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
        }
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
        // 最后 nums1 里剩的元素，自然排在 nums1 最前部，不用再处理。
    }
```

出自 [`977.` 有序数组的平方](https://leetcode.cn/problems/squares-of-a-sorted-array/)。双指针，从数组两端往中间移动，每次比较两端元素，决定 merge 顺序。

```cpp
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        int l = 0, r = n - 1, k = n - 1;
        for (int l = 0, r = n - 1, k = n - 1; k >= 0; k--) {
            res[k] = nums[l] * nums[l] < nums[r] * nums[r] ? pow(nums[r--], 2) : pow(nums[l++], 2);
        }
        return res;
    }
```

# 链表的归并排序（递归法）

完整代码：[`merge-sort-linked-list.cpp`](code/merge-sort-linked-list.cpp)

```cpp
    struct Node {
        int val;
        Node *next;
    };

    void split(Node *h, Node* &a, Node* &b) {
        if (h == nullptr || h->next == nullptr) {
            a = h; b = nullptr;
            return;
        }
        Node *slow = h, *fast = h;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            if (fast == nullptr) {
                break;
            }
            slow = slow->next;
        }
        a = h; b = slow->next; slow->next = nullptr;
    }

    Node *sorted_merge(Node *a, Node *b) {
        Node dummy = {0, nullptr}, *p = &dummy;
        while (a && b) {
            if (a->val < b->val) {
                p->next = a; a = a->next;
            } else {
                p->next = b; b = b->next;
            }
            p = p->next;
        }
        p->next = a ? a : b;
        return dummy.next;
    }

    void merge_sort(Node *&h) {
        // 空、或只有一个节点，不用排序，直接返回
        if (h == nullptr || h->next == nullptr) {
            return;
        }

        Node *a, *b;
        split(h, a, b);
        merge_sort(a);
        merge_sort(b);
        h = sorted_merge(a, b);
    }
```

# 并发

[concurrency vs. traditional](https://gledis.hashnode.dev/exploring-the-efficiency-of-merge-sort-concurrency-vs-traditional-approach)

# 推广

merge sort 特别是其变体如 k-way merge，是一些重要算法的核心。（k-way merge 要用到 priority queue）

- 磁盘上排序 (external sorting)：数据量很大时，通过分批处理适合内存的数据量，优化了磁盘 I/O 操作。
- LSM tree (log-structured merge-tree)：在教学上不太突出，但在实际 db/storage 系统中很重要。通过批量写入和合并操作，提高写入效率、减少磁盘 I/O。在处理大规模数据时尤其重要。
