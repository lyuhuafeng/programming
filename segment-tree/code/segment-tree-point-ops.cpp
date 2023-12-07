#include <cstdio>
#include <algorithm> // std::fill()
using namespace std;

void push_up(float tree[], int i) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
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

// 单点查询：查询 a[where] 的值
float do_point_query(int where, float tree[], int s, int t, int index) {
    if (s == t) {
        return tree[index];
    }
    int m = s + ((t - s) >> 1);
    if (where <= m) {
        return do_point_query(where, tree, s, m, 2 * index);
    } else {
        return do_point_query(where, tree, m + 1, t, 2 * index + 1);
    }
}

// 单点更新：a[k] 值修改为 val
void do_point_update(int k, float val, float tree[], int s, int t, int index) {
    if (s == t) {
        tree[index] = val;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (k <= m) {
        do_point_update(k, val, tree, s, m, 2 * index);
    } else {
        do_point_update(k, val, tree, m + 1, t, 2 * index + 1);
    }
    push_up(tree, index);
}

int main() {
    float a[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int n = sizeof a / sizeof a[0];
    int N = 4 * n;
    float tree[N];
    fill(tree, tree + N, 0.0);
    
    int s = 0, t = n - 1;
    build(a, s, t, tree, 1);
    for (int i = 0; i < N; i++) {
        if (tree[i] > 0.0) {
            printf("%d: %d\n", i, (int) tree[i]);
        }
    }

    int k = 5;
    float val = 8.3;
    float v = do_point_query(k, tree, s, t, 1);
    printf("%f\n", v);

    do_point_update(k, val, tree, s, t, 1);
    v = do_point_query(k, tree, s, t, 1);
    printf("%f\n", v);
    return 0;
}
