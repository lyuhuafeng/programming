#include <cstdio>
#include <utility> // swap()
using namespace std;

// max-heap，parent 大于两个 child
// 下标从 `0` 开始，`i` 的两个子节点下标为 `2*i+1` 和 `2*i+2`，`i` 的父节点为 `(i-1)/2`。

typedef int T;

// 前提：a[start + 1, end] 范围已是 heap；只要把 start 自己下沉到合适位置
void sift_down(T a[], int start, int end) {
    T val = a[start];
    int child;
    while ((child = 2 * start + 1) <= end) { // child: 左child
        if (child + 1 < end && a[child + 1] > a[child]) { // child: 较大child
            child++;
        }
        if (val >= a[child]) { // 若 parent 已大于两个 children，则已下沉完毕，返回
            return;
        }
        a[start] = a[child];
        a[child] = val;  // 否则，swap(start, child), 即：下沉一次
        start = child; // 然后以下沉后的位置为起点，继续下一轮下沉
    }
}

// child 是新加到最后的、可能要上移的节点
// 前提：a[0, child - 1] 范围已是 heap；只要把 child 上浮到合适位置
void sift_up(T a[], int child) {
    T val = a[child];
    int parent;
    while ((parent = (child - 1) / 2) >= 0) {
        if (a[parent] >= val) {
            return;
        }
        a[child] = a[parent];
        a[parent] = val;
        child = parent;
    }
}
// 另一种实现：思路一样，改用 for 循环
void sift_up_v2(T a[], int child) {
    for (int i = child; i > 0 && a[(i - 1) / 2] < a[i]; i /= 2) {
        swap(a[(i - 1) / 2], a[i]);
    }
}

// sift_down 版本，O(n)：从原始序列开始，逆序依次 sift_down 每个 non-leaf 节点
// a[]: 原始序列；n: 元素个数
// 认为所有 leaf 节点均已满足 heap 条件(因为无 child 可比较)，
// 然后依次调整/下沉所有 non-leaf 节点
// n-1: 最后一个 index; (n-1-1) / 2: 最后一个 index 的 parent
void make_heap(T a[], int n) {
    for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
        sift_down(a, i, n - 1);
    }
}

// sift_up 版本，O(nlogn)：从空序列开始，逐个把每个元素插入到最后并 sift_up
void make_heap_v2(T a[], int n) {
    for (int i = 1; i <= n - 1; i++) {
        sift_up(a, i);
    }
}

// 依次把当前最大元素 a[0] 取出，并调整剩下部分，使a[0]重新最大
// 取出的各最大元素放在 array 最后，是 in-place 操作。是不稳定的。
void heap_sort(T a[], int n) {
    make_heap(a, n);
    for (int i = n - 1; i >= 1; i--) {
        swap(a[i], a[0]);
        sift_down(a, 0, i - 1);
    }
}

int main() {
    T a[] = { 3, 9, 2, 4, 12, 1, 23, 17, 8, 4, 13, 2 };
    int n = sizeof a / sizeof a[0];
    heap_sort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}