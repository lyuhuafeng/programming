#include <cstdio>
using namespace std;

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

// merge sort: 排序 a 数组的 [left, right] 闭区间范围
void merge_sort(int a[], int left, int right, int t[]) {
    if (left == right) {
        return;
    }
    int mid = left + (right - left) / 2;
    merge_sort(a, left, mid, t);
    merge_sort(a, mid + 1, right, t);
    merge_lists(a, left, mid, right, t);
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n], t[n];
    for (int i = 0; i < n; i++) { scanf("%d", &a[i]); }
    merge_sort(a, 0, n - 1, t);
    for (int i = 0; i < n; i++) { printf("%d ", a[i]); }
    return 0;
}
