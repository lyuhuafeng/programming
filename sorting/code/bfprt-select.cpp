#include <cstdio>
#include <vector>
#include <algorithm> // for swap
using namespace std;


void display(const vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 标准 insertion sort
void insertion_sort(vector<int>& arr, int start, int n) {
    for (int i = start + 1; i < start + n; i++) {
        int t = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > t) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

// hoare partition scheme
int hoare_partition(vector<int>& arr, int left, int right, int pv) {
    int i = left - 1, j = right + 1;
    while (true) {
        do { i++; } while (arr[i] < pv);
        do { j--; } while (arr[j] > pv);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

// in-place 的，为了找 median-of-medians，把 median-of-5's 挪到了整个 array 的前面
// 若用额外空间
int bfprt_select(vector<int>& arr, int left, int right, int k) {
    printf("bfprt: left:%d, right:%d\n", left, right);
    if (left == right) { return arr[left]; }

    int j = 0;
    for (int i = left; i <= right; i += 5) {
        int size = min(5, right - i + 1);
        printf("  group: i:%d, size:%d\n", i, size);
        insertion_sort(arr, i, size);
        swap(arr[left + j], arr[i + size / 2]);
        j++;
        display(arr);
    }
    j--;

    int mm = bfprt_select(arr, left, left + j, (j + 1) / 2);
    int pi = hoare_partition(arr, left, right, mm);
    int len = pi - left + 1;
    if (len > k) {
        return bfprt_select(arr, left, pi, k);
    } else {
        return bfprt_select(arr, pi + 1, right, k - len); // why not k?
    }
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 4, 19, 26};
    int n = arr.size();
    int k = 4; // 0-indexed

    display(arr);

    int res = bfprt_select(arr, 0, n - 1, k);
    printf("the %d-th smallest element is %d\n", k, res);
    display(arr);

    return 0;
}
