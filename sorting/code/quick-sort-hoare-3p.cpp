#include <utility> // swap()
#include <cstdio>
#include <chrono>
#include <iostream>
using namespace std;

void display(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// little turing 标程。初值 l, r；i, j 谁先动手有规律，见上。
// 好像不能正确处理 duplicate elements?
// 最左边元素值为 pivot 值。对面 j 先动手。
int partition(long a[], int left, int right) {
    long key = a[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && a[j] >= key) { j--; } // j 先动手，往左找第一个 < key 的。
        while (i < j && a[i] <= key) { i++; } // i 随后，往右找第一个  > key 的。
        // 上面两句里 a[i] >= 或 <= key 不能用 > 或 <
        if (i < j) {
            swap(a[i], a[j]);
        } // { else 会自然 break }
    }
    // 循环结束后，i == j
    a[left] = a[i]; a[i] = key; // 相当于 swap(a[left], a[i]);
    return i;
}

// little turing 标程。初值 l, r；i, j 谁先动手有规律，见上。
// 最右边元素值作为 pivot 值。左边 i 先动手。
int partition_2(long a[], int left, int right) {
    long key = a[right];
    int i = left, j = right;
    while (i < j) {
        while (i < j && a[i] <= key) { i++; } // i 先动手，往右找第一个 > key 的。
        while (i < j && a[j] >= key) { j--; } // j 随后，往左找第一个 < key 的。
        // 上面两句里 a[i] >= 或 <= key 不能用 > 或 <
        if (i < j) {
            swap(a[i], a[j]);
        } // { else 会自然 break }
    }
    // 循环结束后，i == j
    a[right] = a[i]; a[i] = key; // 相当于 swap(a[right], a[i]);
    return i;
}

// Sedgewick 'algorithms' 4th ed. p291
int partition_3(long a[], int left, int right) {
    long key = a[left];
    int i = left, j = right + 1;
    while (true) {
        while (a[++i] < key) { if (i == right) break; } // i 向右找第一个 >= k 的
        while (a[--j] > key) { if (j == left) break; } // j 向左找第一个 <= k 的
        if (i >= j) { break; }
        swap(a[i], a[j]);
    }
    a[left] = a[j], a[j] = key; // 相当于 swap(a[l], a[j])
    return j;
}

void qsort(long a[], int left, int right) {
    if (left < right) {
        int pi = partition_3(a, left, right);
        qsort(a, left, pi - 1); // 左侧：递归
        qsort(a, pi + 1, right); // 右侧：不递归
    }
}

void qsort_2(long a[], int left, int right) {
    while (left < right) {
        int pi = partition(a, left, right);
        qsort_2(a, left - 1, pi); // 左侧：递归
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

    auto t0 = std::chrono::steady_clock::now();
    qsort(nums, 0, n - 1);
    auto t1 = std::chrono::steady_clock::now();
    cerr << "cost " << chrono::duration<double>(t1 - t0).count() << " seconds" << endl;

    for (int i = 0; i < n; i++) {
        printf("%ld ", nums[i]);
    }
    printf("\n");

    return 0;
}
