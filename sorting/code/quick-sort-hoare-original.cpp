#include <utility> // swap()
#include <vector>
#include <cstdio>
using namespace std;

void display(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

    // impl 1
    // 来自 wikipedia https://en.wikipedia.org/wiki/Quicksort 和 mit「算法导论」书
    // 两者基本一致，只是 j 循环 和 i 循环 顺序相反。但谁先谁后都可以。
    int partition(long nums[], int l, int r) {
        long key = nums[l];
        int i = l - 1, j = r + 1;
        while (true) {
            do { i++; } while (nums[i] < key); // wiki: 此句在前
            do { j--; } while (nums[j] > key); // book: 此句在前
            if (i >= j) {
                return j;
            }
            swap(nums[i], nums[j]);
        }
    }

    // impl 2
    // ref: leetcode 215. 数组中的第K个最大元素 官方题解
    int partition_2(long nums[], int l, int r) {
        long key = nums[l];
        int i = l - 1, j = r + 1;
        while (i < j) {
            do { i++; } while (nums[i] < key);
            do { j--; } while (nums[j] > key);
            if (i < j) {
                swap(nums[i], nums[j]);
            }
        }
        return j;
    }

    // impl 3
    // 对 impl 1 改进了一点，先 i++/j-- 再对 i/j 做循环，从而把 do ... while 循环变成了 while 循环
    int partition_3(long nums[], int l, int r) {
        long key = nums[l];
        int i = l - 1, j = r + 1;
        while (true) {
            i++;
            while (nums[i] < key) { i++; }
            j--;
            while (nums[j] > key) { j--; }
            if (i >= j) {
                return j;
            }
            swap(nums[i], nums[j]);
        }
    }

    void qsort(long a[], int left, int right) {
        if (left < right) {
            int pi = partition_3(a, left, right);
            qsort(a, left, pi); // 左侧：递归
            qsort(a, pi + 1, right); // 右侧：不递归
        }
    }

    void qsort_2(long a[], int left, int right) {
        while (left < right) {
            int pi = partition_3(a, left, right);
            qsort_2(a, left, pi); // 左侧：递归
            left = pi + 1; // 右侧：不递归
        }
    }


int main() {
    // long nums[] = {
    //     548813502, 592844616, 715189364, 844265744, 602763370,
    //     857945619, 544883177, 847251737, 423654796, 623563696,
    //     645894115, 384381708, 437587209, 297534605, 891773001,
    //     56712975, 963662764, 272656294, 383441521, 477665111,
    //     791725033, 812168726, 528894921, 479977171, 568044563,
    //     392784793, 925596633, 836078768, 71036058, 337396161,
    //     87129296, 648171876, 20218399, 368241537, 832619842,
    //     957155154, 778156756, 140350777, 870012145, 870087251,
    //     978618342, 473608040, 799158563, 800910752, 461479362
    // };
    // int n = sizeof nums / sizeof nums[0];

    int n;
    scanf("%d", &n);
    long nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%ld", &nums[i]);
    }
    
    // display(nums, n);
    qsort_2(nums, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%ld ", nums[i]);
    }
    printf("\n");

    return 0;
}