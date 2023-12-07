#include <cstdio>
#include <algorithm> // std::fill()
using namespace std;

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
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

// a[l,r] 为查询区间，index 为线段树当前节点的编号，[s,t] 为该节点对应的区间
float do_query(int l, int r, float tree[], int s, int t, int index) {
    // 当前区间为询问区间的子集时，直接返回当前区间的 sum
    if (l <= s && t <= r) {
        return tree[index];
    }
    int m = s + (t - s) / 2;
    float sum = 0;
    // 如果左儿子代表的区间 [s,m] 与询问区间有交集,则递归查询左儿子
    if (l <= m) { // 查询左界 <= 左子右界
        sum += do_query(l, r, tree, s, m, index * 2);
    }
    // 如果右儿子代表的区间 [m+1,t] 与询问区间有交集,则递归查询右儿子
    if (r > m) { // r >= m+1: 查询右界 >= 右子左界
        sum += do_query(l, r, tree, m + 1, t, index * 2 + 1);
    }
    return sum;
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
    int l = 3, r = 5;
    printf("sum(%d, %d): %f\n", l, r, do_query(l, r, tree, s, t, 1));

    fill(tree, tree + N, 0.0);
    s = 3, t = n - 3;
    build(a, s, t, tree, 1);
    for (int i = 0; i < N; i++) {
        if (tree[i] > 0.0) {
            printf("%d: %d\n", i, (int) tree[i]);
        }
    }
    l = 3, r = 5;
    printf("sum(%d, %d): %f\n", l, r, do_query(l, r, tree, s, t, 1));
    printf("sum(%d, %d): %f\n", l, r, do_query(l - s, r - s, tree, 0, t - s, 1));

    return 0;
}
