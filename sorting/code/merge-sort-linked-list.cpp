#include <cstdio>
using namespace std;

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

int main() {}
