    ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) { return l2; }
        if (l2 == nullptr) { return l1; }
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        l2->next = mergeTwoLists(l2->next, l1);
        return l2;
    }
