# 合并 k 个升序链表或有序数组

- [`leet 23.` 合并 k 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)
- [`lint 486.` 合并 k 个有序数组](https://www.lintcode.com/problem/486/)

<font color="brown">注意</font>，这里的 merge sort 法，与普通的 merge sort 相比，有一点不同。
- 普通：`if (l == r) { return; }`
- 这里：`if (l == r) { return lists[l]; }`
为什么？因为普通 merge sort，是在一个序列里 in-place 合并，不返回新的子序列；这里是合并多个序列，要返回新的序列。

# 合并 k 个升序链表

所有链表的节点总数为 `N`。

- heap 法
  - 时间 `O(NlogK)`，其中 `logK` 是每次把一个节点放入 heap 中耗时。
  - 空间 `O(K)`，heap 大小。
- merge sort 法
  - 时间 `O(NlogK)`，其中 `logK` 是 `K` 个链表二分。
  - 空间 `O(1)`，合并两个链表所需额外空间。

## 法一：用 heap

用 priority queue 找出每次的最小值。确切地说，是各链表的头结点里最小的。

每次要得到 min，所以用 min-heap，与缺省的相反。所以，比较函数里，`>` 对应 `true`，也与缺省的相反。

因堆里可能有空链表，所以定义空链表的值最小。

为何要允许堆里有空链表？为了用 `(lists.begin(), lists.end())` 做参数初始化 pq，方便处理题目数据里有空链表的情况。但，后续不会再往堆里放入新的空链表。

c++ 代码中，如何初始化 priority_queue？
- 正确做法：`priority_queue<ListNode *, vector<ListNode *>, node_greater>`，但显然数据类型太笨重。
  - 其中 `node_greater` 是结构体或类内重载 `operator()`，不能是简单的比较函数。<font color="red">to check why</font>
- 错误做法：`priority_queue<ListNode *>` 轻巧。但需重载 `operator<()`，其两个参数不能是指针类型。偏偏本题貌似只能用指针类型。所以只能笨重点了。

Java 代码里，不允许 pq 中有空链表，所以把非空链表逐个放入 pq。

C++ 代码
```cpp
    /*
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode() : val(0), next(nullptr) {}
    *     ListNode(int x) : val(x), next(nullptr) {}
    *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    * };
    */

    class node_greater {
    public:
        bool operator()(const ListNode* l1, const ListNode *l2) {
            if (l1 == nullptr) { return false; }
            if (l2 == nullptr) { return true; }
            return l1->val > l2->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head, *p = &head;
        priority_queue<ListNode *, vector<ListNode *>, node_greater> pq(lists.begin(), lists.end());
        while (!pq.empty()) {
            ListNode *l = pq.top(); pq.pop();
            if (l == nullptr) { continue; }
            p->next = l;
            p = l;
            if (l->next != nullptr) {
                pq.push(l->next); // 不会再放入新的空链表
            }
        }
        return head.next;
    }
```

Java 代码

```java
    /*
    * public class ListNode {
    *     int val;
    *     ListNode next;
    *     ListNode() {}
    *     ListNode(int val) { this.val = val; }
    *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    * }
    */

    class ListNodeComparable implements Comparable<ListNodeComparable> {
        ListNode ptr;

        ListNodeComparable(ListNode ptr_) {
            this.ptr = ptr_;
        }

        public int compareTo(ListNodeComparable o) {
            return this.ptr.val > o.ptr.val ? 1 : -1;
        }    
    }

class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNodeComparable> pq = new PriorityQueue<>();
        for (ListNode l : lists) {
            if (l != null) {
                pq.add(new ListNodeComparable(l));
            }
        }
        ListNode head = new ListNode(0);
        ListNode p = head;
        while (!pq.isEmpty()) {
            ListNode l = pq.poll().ptr;
            p.next = l;
            p = l;
            if (l.next != null) {
                pq.add(new ListNodeComparable(l.next));
            }
        }
        return head.next;
    }
}
```

## 法二：merge sort

对 k 个链表做「merge」，就像对 k 个数做「merge sort」一样，有点神奇。有空时再体会体会。

`merge_two()`，合并两个有序链表，两种方法。其中，递归法，巧妙。

```cpp
    // 合并两个，递归法
    ListNode* merge_two(ListNode *a, ListNode *b) {
        if (a == nullptr) { return b; }
        if (b == nullptr) { return a; }
        if (a->val < b->val) {
            a->next = merge_two(a->next, b);
            return a;
        }
        b->next = merge_two(b->next, a);
        return b;
    }
    // 合并两个，非递归法
    ListNode* merge_two(ListNode* l1, ListNode* l2) {
        ListNode dummy, *h = &dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                h->next = l1;
                l1 = l1->next;
            } else {
                h->next = l2;
                l2 = l2->next;
            }
            h = h->next;
        }
        h->next = (l1 ? l1 : l2);
        return dummy.next;
    }

    ListNode* merge(vector<ListNode *> lists, int l, int r) {
        if (l == r) { return lists[l]; }
        int m = l + (r - l) / 2;
        ListNode *a = merge(lists, l, m);
        ListNode *b = merge(lists, m + 1, r);
        return merge_two(a, b);
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) { return nullptr; }
        int n = lists.size();
        return merge(lists, 0, n - 1);
    }
```

# 合并k 个已排好序的数组

采用 merge sort 思路。

```cpp
    // 先分配足够空间，免得每次 push_back()，可能效率高点
    vector<int> merge_2arrays(const vector<int>& v, const vector<int>& u) {
        int vl = v.size(), ul = u.size();
        vector<int> ans(vl + ul);
        int i = 0, j = 0, p = 0;
        while (i < vl && j < ul) { ans[p++] = v[i] < u[j] ? v[i++] : u[j++]; }
        while (i < vl) { ans[p++] = v[i++]; }
        while (j < ul) { ans[p++] = u[j++]; }
        return ans;
    }

    vector<int> merge(vector<vector<int>> &arrays, int l, int r) {
        if (l == r) { return arrays[l]; }
        if (l + 1 == r) { return merge_2arrays(arrays[l], arrays[r]); } // 这句也可不要
        int m = l + (r - l) / 2;
        vector<int> v = merge(arrays, l, m);
        vector<int> u = merge(arrays, m + 1, r);
        return merge_2arrays(v, u);
    }

    vector<int> mergekSortedArrays(vector<vector<int>> &arrays) {
        if (arrays.empty()) { return {}; }
        return merge(arrays, 0, arrays.size() - 1);
    }
```
