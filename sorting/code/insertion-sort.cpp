#include <vector>
#include <utility> // swap()
#include <iostream>
using namespace std;

void insertion_sort(int a[], int n) {
    for (int i = 1; i <= n - 1; i++) {
        // 把位置 i 的元素(未排序区第一个元素)放到到合适的位置
        // 如果 a[i] 比前一个小，说明 a[i] 位置不对，需要挪。
        if (a[i] < a[i - 1]) {
            int t = a[i];   // t: 未排序区的第一个元素，记录下来，待后面使用
            int j;
            for (j = i - 1; j >= 0 && a[j] > t; j--) {  // a[j]>t 而不是>=t，保持稳定性
                a[j + 1] = a[j];    // 位置j的元素右移，位置j可认为已经空了(尽管实际上还在)
            }
            // j循环结束后，所有比t大的元素都右移了一位，给t腾出了地方。
            // 把t放到空出来的地方 (j+1) 即可。+1是因为循环结束时多减了1.
            a[j + 1] = t;
        }
    }
}

void insertion_sort_2(int a[], int n) {
    for (int i = 1; i <= n - 1; i++) {
        // 把 a[i] (未排序区第一个元素) 插入到合适的位置
        // 只要后面的小（已排序区是从小到大排），就往前交换
        for (int j = i - 1; j >= 0 && a[j + 1] < a[j] ; j--) {
            swap(a[j + 1], a[j]);
        }
    }
}

void display(int nums[], int n) {
    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}
int main() {
    int nums[] = {6, 1, 7, 8, 9, 3, 5, 4, 2};
    insertion_sort(nums, sizeof nums / sizeof(int));
    display(nums, sizeof nums / sizeof nums[0]);
}