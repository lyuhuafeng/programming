#include <cstdio>
#include <algorithm>
using namespace std;

int get_max(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        mx = max(mx, arr[i]);
    }
    return mx;
}

// 对 arr[n]，根据 exp 表示的第 k 位，做 counting sort。
// exp = 10 ^ (k-1)，k 从 1 算起。
// 例，3547，从低往高（右 -> 左），第 3 位，对应：exp = 10^2, 这一位上的数字为 (3547 / 10^2) % 10 = 5
void count_sort(int a[], int n, int exp) {
    int count[10];
    fill_n(count, 10, 0);

    // 统计数字出现的次数
    for (int i = 0; i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }
    // 求前缀和，将「出现个数」转换为「数组索引」
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    int output[n]; // 输出数组
    for (int i = n - 1; i >= 0; i--) {
        int t = (a[i] / exp) % 10;
        output[count[t] - 1] = a[i];
        count[t]--;
    }

    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
}

void radix_sort(int arr[], int n) {
    int m = get_max(arr, n);
    // 最低位 -> 最高位（右 -> 左），依次对每一位排序
    for (int exp = 1; exp <= m; exp *= 10) { // 'exp <= m' 另一种写法：'m / exp > 0'
        count_sort(arr, n, exp);
    }
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof arr / sizeof arr[0];

    radix_sort(arr, n);
    print(arr, n);
    return 0;
}
