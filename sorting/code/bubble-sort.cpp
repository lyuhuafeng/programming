#include <cstdio>
#include <utility>  // swap()
using namespace std;

void display(int[], int);

/*
last_swapped（记作 e）: 记录最后一次交换发生的位置, e 和 e+1 这两个位置交换。
交换之后，e+1 进入「已排序区」，e 还在「未排好序区」中。
下次循环到 e-1，不包括 e。因为，若需交换，则 (e-1, e) 可覆盖 e。
所以，每次循环的终点，都是 k=e-1。为了方便 k 的第一次设置，last_swapped 的初值设为 n-1，是「下标最大值」。
*/
void bubble_sort(int a[], int n) {
    int last_swapped = n - 1;
    while (last_swapped > 0) {
        int k = last_swapped - 1;
        last_swapped = 1;
        for (int j = 0; j <= k; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                last_swapped = j;
            }
        }
    }
}

void bubble_sort_extended(int a[], int l, int r) {
    int border = r;
    while (border > l) {
        int last_swapped = l - 1;
        for (int j = l; j <= border - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                last_swapped = j;
            }
        }
        border = last_swapped;
        // display(a, l, r, border);
    }
}


int main() {
    int nums[] = {8,7,6,5}; //{6, 1, 9, 7, 8, 3, 5, 4, 2, 0};
    int len = sizeof nums / sizeof(int);
    display(nums, len);
    bubble_sort(nums, len);
    // bubble_sort_extended(nums, 0, len - 1);
    display(nums, len);
    return 0;
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
