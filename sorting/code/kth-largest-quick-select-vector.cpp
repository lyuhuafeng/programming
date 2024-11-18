#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

// lomuto, 分三段，qselect 递归
int partition(vector<int>& a, int l, int r) {
    int key = a[r]; // 最后一个元素作为pivot值
    int p = l - 1;   // “小于等于区”的右边界
    for (int j = l; j <= r - 1; j++) { // 找小于key的
        if (a[j] <= key) {
            swap(a[++p], a[j]);
        }
    }
    swap(a[++p], a[r]);
    return p;
}

void qselect(vector<int>& a, int l, int r, int k) {
    // assert(left <= right); // 这个 assertion 对 qsort() 不成立
    if (l == r) { return; }
    int pi = partition(a, l, r);
    if (pi == k) {
        return;
    } else if (pi > k) {
        qselect(a, l, pi - 1, k);
    } else {
        qselect(a, pi + 1, r, k);
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
