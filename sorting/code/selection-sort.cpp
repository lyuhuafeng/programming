#include <utility>  // swap()
using namespace std;

void display(int[], int);

void selection_sort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        // 从未排序区 [i, n - 1] 里挑出最小的
        // 位置 i 是未排序区的起点。
        // [0, i - 1] 是已排序区。
        int min_num = a[i];
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < min_num) {
                min_num = a[j];
                min_index = j;
            }
        }
        // 未排序区里最小的 (min_index) 与未排序区第一个 (i) 交换
        // 位置 i 变成已排序区的最后一个
        swap(a[min_index], a[i]);
        display(a, n);
    }
}

int main() {
    int nums[] = {6, 1, 9, 7, 8, 3, 5, 4, 2, 0};
    int len = sizeof nums / sizeof(int);
    display(nums, len);
    selection_sort(nums, len);
    display(nums, len);
    return 0;
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
