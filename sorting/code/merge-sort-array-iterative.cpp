// merge sort, iteratively, bottom-up

#include <cstdio>
#include <algorithm> // min()
using namespace std;

// 与递归法里的 merge_lists() 一样
// helper: 归并 a 数组的 [left, mid]、[mid + 1, right] 两个闭区间
void merge_lists(int a[], int left, int mid, int right, int t[]) {
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        t[k++] = a[i] > a[j] ? a[j++] : a[i++];
    }
    while (i <= mid) {
        t[k++] = a[i++];
    }
    while (j <= right) {
        t[k++] = a[j++];
    }
    for (i = left, k = 0; i <= right; i++, k++) {
        a[i] = t[k];
    }
}

void merge_sort(int a[], int n, int t[]) {
    // cur: 当前要 merge 的子区间的「半长度」，从 1 开始，每次加倍最大不超过 n - 1，
    for (int cur = 1; cur <= n - 1; cur *= 2) {
        printf("len:%d\n", cur);
        for (int l = 0; l < n - 1; l += 2 * cur) {
            int m = l + cur - 1;
            int r = min(l + 2 * cur - 1, n - 1);
            printf("  l:%d, m:%d, r:%d\n", l, m, r);
            merge_lists(a, l, m, r, t); // [l,m] [m+1,r] 与递归法里的 merge_lists() 一样
        }
    }
}

int main() {
    int a[] = {1, 12, 3, 20, 5, 0, 7, 6, 9, 2, 15, 4, 16, 14, 13, 8};
    int n = sizeof a / sizeof a[0];
    printf("n:%d\n", n);
    int t[n];
    merge_sort(a, n, t);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}