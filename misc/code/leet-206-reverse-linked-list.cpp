/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

    ListNode* reverseList(ListNode* head) {
        ListNode *prv = nullptr;
        ListNode *cur = head;
        while (cur != nullptr) {
            // 先记录 next = cur->next, 然后依次顶针更新至 curr
            ListNode *nxt = cur->next;
            cur->next = prv;
            prv = cur;
            cur = nxt;
        }
        return prv;
    }
