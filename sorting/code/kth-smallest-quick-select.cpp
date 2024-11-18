#include <cstdio>
#include <utility> // swap()
using namespace std;

int partition(int a[], int left, int right) {
    int key = a[right]; // 最后一个元素作为pivot值
    int p = left - 1;   // “小于等于区”的右边界
    for (int j = left; j <= right - 1; j++) { // 找小于key的
        if (a[j] <= key) {
            swap(a[++p], a[j]);
        }
    }
    swap(a[++p], a[right]);
    return p;
}

void qselect(int a[], int left, int right, int k) {
    // assert(left <= right); // 这个 assertion 对 qsort() 不成立
    if (left == right) {
        return;
    }
    int pi = partition(a, left, right);
    if (pi == k) {
        return;
    } else if (pi > k) {
        qselect(a, left, pi - 1, k);
    } else {
        qselect(a, pi + 1, right, k);
    }
}

void kth_smallest(int a[], int n, int k) {
    qselect(a, 0, n - 1, k);
}

int main() {
    int a[] = {3,2,1,5,6,4};
    int n = sizeof a / sizeof(int);
    int k = 3;
    kth_smallest(a, n, k);
    printf("k-th smallest: %d\n", a[k]);
    printf("k smallests: ");
    for (int i = 0; i <= k; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
