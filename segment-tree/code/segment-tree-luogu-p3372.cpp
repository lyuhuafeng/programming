#include <cstdio>
#include <algorithm> // fill()
using namespace std;

void display(int tree[], int lazy[], int N) {
    for (int i = 0; i < N; i++) {
        if (tree[i] > 0 || lazy[i] > 0) {
            printf("%d: node:%d, lazy:%d\n", i, tree[i], lazy[i]);
        }
    }
    printf("\n");
}
void push_up(long long tree[], int i) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
}
void push_down(long long tree[], long long lazy[], int s, int m, int t, int i) {
    tree[2 * i] += lazy[i] * (m - s + 1);
    lazy[2 * i] += lazy[i];
    tree[2 * i + 1] += lazy[i] * (t - m);
    lazy[2 * i + 1] += lazy[i];
    lazy[i] = 0;
}
void build(long long a[], int s, int t, long long tree[], int i) {
    if (s == t) {
        tree[i] = a[s];
        return;
    }
    int m = s + (t - s) / 2;
    build(a, s, m, tree, 2 * i);
    build(a, m + 1, t, tree, 2 * i + 1);
    push_up(tree, i);
}
void do_add(long long a[], int l, int r, int k, long long tree[], long long lazy[], int s, int t, int i) {
    if (k == 0) {
        return;
    }
    if (l <= s && t <= r) {
        tree[i] += k * (t - s + 1);
        if (s != t) {
            lazy[i] += k;
        }
        return;
    }
    int m = s + (t - s) / 2;
    if (lazy[i] != 0) {
        push_down(tree, lazy, s, m, t, i);
    }
    if (l <= m) {
        do_add(a, l, r, k, tree, lazy, s, m, 2 * i);
    }
    if (r >= m + 1) {
        do_add(a, l, r, k, tree, lazy, m + 1, t, 2 * i + 1);
    }
    push_up(tree, i);
}
long long do_query(long long a[], int l, int r, long long tree[], long long lazy[], int s, int t, int i) {
    if (l <= s && t <= r) {
        return tree[i] /*+ lazy[i] * (t - s + 1)*/;
    }
    int m = s + (t - s) / 2;
    if (lazy[i] != 0) {
        push_down(tree, lazy, s, m, t, i);
    }
    long long sum = 0;
    if (l <= m) {
        sum += do_query(a, l, r, tree, lazy, s, m, 2 * i);
    }
    if (r >= m + 1) {
        sum += do_query(a, l, r, tree, lazy, m + 1, t, 2 * i + 1);
    }
    return sum;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    long long a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    int N = 4 * n;
    long long tree[N], lazy[N];
    fill(tree, tree + N, 0l);
    fill(lazy, lazy + N, 0l);
    int s = 1, t = n;
    build(a, s, t, tree, 1);
    // display(tree, lazy, N);

    int op, x, y, k;
    while (m--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            scanf("%d", &k);
            // printf("op:1, %d, %d, %d\n", x, y, k);
            do_add(a, x, y, k, tree, lazy, s, t, 1);
            // display(tree, lazy, N);
        } else {
            // printf("op:2, %d, %d\n", x, y);
            printf("%lld\n", do_query(a, x, y, tree, lazy, s, t, 1));
            // display(tree, lazy, N);
        }
    }
    return 0;
}