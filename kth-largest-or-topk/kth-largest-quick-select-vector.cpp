#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

int partition(vector<int>& a, int left, int right) {
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

void qselect(vector<int>& a, int left, int right, int k) {
    // assert(left <= right); // 这个 assertion 对 qsort() 不成立
    if (left == right) {
        return;
    }
    int pivot = partition(a, left, right);
    if (pivot == k) {
        return;
    } else if (pivot > k) {
        qselect(a, left, pivot - 1, k);
    } else {
        qselect(a, pivot + 1, right, k);
    }
}

void kth_largest(vector<int>& a, int k) {
    k = a.size() - k;
    qselect(a, 0, a.size() - 1, k);
}

int main() {
    vector<int> a = {3,2,1,5,6,4};
    int k = 2;

    kth_largest(a, k);
    printf("k-th largest: %d\n", a[a.size() - k]);
    for (int i = a.size() - 1; i >= a.size() - k; i--) {
        printf("%d ", a[i]);
    }
    return 0;
}
