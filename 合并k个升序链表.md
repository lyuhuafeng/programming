## [leetcode 23: 合并 k 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)

思路：

用 priority queue 找出每次的最小值。

每次要得到 min，所以用 min-heap，与缺省的相反。所以比较函数里，> 对应 true，也与缺省的相反。

因堆里可能有空链表，所以定义空链表的值最小。

为何要允许堆里有空链表？为了用 `(lists.begin(), lists.end())` 做参数初始化 pq。

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
        if (l1 == nullptr) {
            return false;
        }
        if (l2 == nullptr) {
            return true;
        }
        return l1->val > l2->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head, *p = &head;
        priority_queue<ListNode *, vector<ListNode *>, node_greater> pq(lists.begin(), lists.end());
        while (!pq.empty()) {
            ListNode *l = pq.top(); pq.pop();
            if (l == nullptr) { continue; }
            p->next = l;
            p = l;
            if (l->next != nullptr) {
                pq.push(l->next);
            }
        }
        return head.next;
    }
};
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
