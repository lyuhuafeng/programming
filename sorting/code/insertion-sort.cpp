#include <vector>
#include <utility> // swap()
#include <cstdio>
using namespace std;

void insertion_sort(int a[], int n) {
    for (int i = 1; i <= n - 1; i++) {
        // 把位置 i 的元素(未排序区第一个元素)放到到合适的位置
        // 如果 a[i] 比前一个小，说明 a[i] 位置不对，需要挪。
        if (a[i] < a[i - 1]) {
            int t = a[i];   // t: 未排序区的第一个元素，记录下来，待后面使用
            int j;
            for (j = i - 1; j >= 0 && a[j] > t; j--) {  // a[j]>t 而不是 >=t，保持稳定性
                a[j + 1] = a[j];    // 位置 j 的元素右移，位置 j 可认为已经空了(尽管实际上还在)
            }
            // j 循环结束后，所有比 t 大的元素都右移了一位，给 t 腾出了地方。
            // 把 t 放到空出来的地方 (j+1) 即可。+1 是因为循环结束时多减了 1。
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

void insertion_sort_3(vector<float>& bkt) {
    for (int i = 1; i < bkt.size(); ++i) { // 注意从 1 开始。第 0 个元素是「已排序区」的初始态。
        float t = bkt[i];
        int j = i - 1;
        while (j >= 0 && bkt[j] > t) { // 注意 bkt[j] > t 而不是「>=」，为保持稳定性。
            bkt[j + 1] = bkt[j];
            j--;
        }
        bkt[j + 1] = t;
    }
}

//// stable binary insertion sort
struct entry {
    int val;
    int idx;
};
// 在左闭右开区间 [0 ... n) 范围内，找第一个大于 key 的位置（下标）
int bsearch(const vector<entry> &v, int n, int key) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m].val > key) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}
void binary_insertion_sort(vector<entry> &a) {
    int n = a.size();
    for (int i = 1; i <= n - 1; i++) {
        // 把位置 i 的元素(未排序区第一个元素)放到到合适的位置
        // 如果 a[i] 比前一个小，说明 a[i] 位置不对，需要挪。
        if (a[i].val < a[i - 1].val) {
            entry t = a[i];   // t: 未排序区的第一个元素，记录下来，待后面使用
            int idx = bsearch(a, i, t.val);
            for (int j = i - 1; j >= idx; j--) {
                a[j + 1] = a[j];    // 位置 j 的元素右移，位置 j 可认为已经空了(尽管实际上还在)
            }
            // j 循环结束后，所有比 t 大的元素都右移了一位，给 t 腾出了地方。
            // 把 t 放到空出来的地方 (idx) 即可。
            a[idx] = t;
        }
    }
}


void display(int nums[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
void display(const vector<entry> &v) {
    for (entry e : v) {
        printf("%d(%d) ", e.val, e.idx);
    }
    printf("\n");
}

int main() {
    int nums[] = {6, 1, 7, 8, 9, 6, 2, 7, 1, 2, 3, 5, 4, 2};
    int n = sizeof nums / sizeof(int);
    vector<entry> v;
    for (int i = 0; i < n; i++) {
        v.push_back({nums[i], i});
    }

    insertion_sort(nums, n);
    // binary_insertion_sort(nums, n);
    display(nums, n);
    display(v);
    binary_insertion_sort(v);
    display(v);
    return 0;
}