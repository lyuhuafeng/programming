#include <cstdio>
#include <algorithm> // std::fill()
using namespace std;

void push_up(float tree[], int i) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
}
void push_down(float tree[], float lazy[], int s, int m, int t, int index) {
    tree[2 * index] += (m - s + 1) * lazy[index];
    lazy[2 * index] += lazy[index];

    tree[2 * index + 1] += (t - m) * lazy[index];
    lazy[2 * index + 1] += lazy[index];

    lazy[index] = 0;
}

// 对 a[s, t] 区间建立线段树（可能是整棵树，也可能是整棵树的一个子树）
// 树的根节点编号为 index
void build(float a[], int s, int t, float tree[], int index) {
    if (s == t) {
        tree[index] = a[s];
        return;
    }
    int m = s + (t - s) / 2;
    // 递归到左右子树。tree node 下标从 1 开始，故左右子节点的下标为 2i, 2i+1。
    build(a, s, m, tree, index * 2);
    build(a, m + 1, t, tree, index * 2 + 1);
    push_up(tree, index);
}

float do_query(int l, int r, float tree[], float lazy[], int s, int t, int index) {
    if (l <= s && t <= r) {
        return tree[index];
    }
    float sum = 0;
    int m = s + ((t - s) >> 1);

    if (lazy[index] != 0) {
        push_down(tree, lazy, s, m, t, index);
    }

    if (l <= m) {
        sum += do_query(l, r, tree, lazy, s, m, 2 * index);
    }
    if (r > m) {
        sum += do_query(l, r, tree, lazy, m + 1, t, 2 * index + 1);
    }
    return sum;
}

// 更新：a[l, r] 范围，每个元素增加 x。线段树的当前节点为 index，对应范围 [s, t]
void do_add(int l, int r, float x, float tree[], float lazy[], int s, int t, int index) {
    if (x == 0.0) {
        return;
    }
    if (l <= s && t <= r) {
        tree[index] += (t - s + 1) * x;
        if (s != t) { // 我有子区间，才需标记 lazy
            lazy[index] += x;
        }
        return;
    }

    int m = s + ((t - s) >> 1);

    if (lazy[index] != 0) {
        push_down(tree, lazy, s, m, t, index);
    }

    if (l <= m) {
        do_add(l, r, x, tree, lazy, s, m, 2 * index);
    }
    if (r > m) {
        do_add(l, r, x, tree, lazy, m + 1, t, 2 * index + 1);
    }
    push_up(tree, index);
}

int main() {
    float a[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int n = sizeof a / sizeof a[0];
    printf("n:%d\n", n);
    int N = 4 * n;
    float tree[N], lazy[N];
    fill(tree, tree + N, 0.0);
    fill(lazy, lazy + N, 0.0);

    int s = 0, t = n - 1;
    build(a, s, t, tree, 1);
    for (int i = 0; i < N; i++) {
        if (tree[i] > 0.0) {
            printf("%d: %d\n", i, (int) tree[i]);
        }
    }
    int l = 3, r = 5;
    printf("sum(%d, %d): %f\n", l, r, do_query(l, r, tree, lazy, s, t, 1));

    do_add(4, 8, .15, tree, lazy, s, t, 1);
    l = 3, r = 9;
    printf("sum(%d, %d): %f\n", l, r, do_query(l, r, tree, lazy, s, t, 1));

    return 0;
}

