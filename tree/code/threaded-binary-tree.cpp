#include <cstdio>
using namespace std;

// reference: https://xiuxin.gitbook.io/datastructre/shu-he-er-cha-shu/xian-suo-er-cha-shu
// -std=c++11: nullptr

typedef int ElemType;
struct node {
    ElemType data;
    node *lchild, *rchild;
    int ltag, rtag;
};

void in_thread(node *& p, node *& pre) { //线索二叉树的根结点，指向前驱结点的指针
    if (p == nullptr) {
        return;
    }
    in_thread(p->lchild, pre);   // 递归，线索化左子树
    if (p->lchild == nullptr) {  // 左子树为空，建立前驱线索
        p->lchild = pre;
        p->ltag = 1;
    } else {
        p->ltag = 0;
    }
    if (pre != nullptr) {
        if (pre->rchild == nullptr) {
            pre->rchild = p;      //建立前驱结点的后继线索
            pre->rtag = 1;
        } else {
            pre->rtag = 0;
        }
    }
    pre = p;                      //标记当前结点成为刚刚访问过得结点
    in_thread(p->rchild, pre);    //递归，线索化右子树
}

// 以 p 为 root 的二叉树线索化
void create_in_thread(node * p){
    if (p == nullptr) {
        return;
    }
    node *pre = nullptr;
    in_thread(p, pre);        // 线索化
    pre->rchild = nullptr;    // 处理遍历的最后一个结点
    pre->rtag = 1;
}

// 不含头结点的 in-order threaded binary tree 的 in-order traverse
// in-order, first node
node* first_node(node* p){
    while (p->ltag == 0){
        p = p->lchild;
    }
    return p;   
}
// in-order, next node of p
node* next_node(node* p) {
    return p->rtag == 0 ? first_node(p->rchild) : p->rchild;
}

// in-order traverse
void in_order(node* t){
    for (node *p = first_node(t); p != nullptr; p = next_node(p)) {
        //// visit(p);
    }
}

// in-order, last node
node* last_node(node* p) {
    while (p->rtag == 0) {
        p = p->rchild;
    }
    return p;
}
// in-order, previous node of p
node* pre_node(node* p) {
    return (p->ltag == 0) ? first_node(p->lchild) : p->lchild;
}

int main() {}