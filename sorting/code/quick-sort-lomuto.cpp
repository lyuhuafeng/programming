#include <utility> // swap()
#include <cstdio>
using namespace std;

/*
void display(const long long a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d]:%lld ", i, a[i]);
    }
    printf("\n");
}
void display_p(const long long a[], int l, int r, int pi) {
    printf("   after: l:%d, r:%d, p_idx:%d: ", l, r, pi);
    for (int i = l; i <= r; i++) {
        if (i == pi) {
            printf("_[%d]:%lld_ ", i, a[i]);
        } else {
           printf("[%d]:%lld ", i, a[i]);
        }
    }
    printf("\n");
}
*/

int partition(long long a[], int left, int right) {
    long long key = a[right]; // 最后一个元素作为 pivot 值
    // printf("__partition\n  before: l:%d, r:%d, p_val:%d: ", left, right, key);
    // display(a, right + 1);
    int p = left - 1;   // 「小于等于区」的右边界
    for (int j = left; j <= right - 1; j++) {
        if (a[j] <= key) { // 找 <= key 的，放到 pivot 左边。用「<」也可以。
            swap(a[++p], a[j]);
        }
    }
    swap(a[++p], a[right]);
    return p;
}

void qsort(long long a[], int left, int right) {
    if (left >= right) { // 必须是 >= 而不是 ==。有时 pivot == left 或 right，导致下一次调用时 left > right。
        return;
    }
    int pivot = partition(a, left, right);
    // display_p(a, left, right, pivot);
    qsort(a, left, pivot - 1);
    qsort(a, pivot + 1, right);
}

int main() {
    long long nums[] = {
        548813502, 592844616, 715189364, 844265744, 602763370,
        857945619, 544883177, 847251737, 423654796, 623563696,
        645894115, 384381708, 437587209, 297534605, 891773001,
        56712975, 963662764, 272656294, 383441521, 477665111,
        791725033, 812168726, 528894921, 479977171, 568044563,
        392784793, 925596633, 836078768, 71036058, 337396161,
        87129296, 648171876, 20218399, 368241537, 832619842,
        957155154, 778156756, 140350777, 870012145, 870087251,
        978618342, 473608040, 799158563, 800910752, 461479362
    };
    int n = sizeof nums / sizeof nums[0];

    /*
    int n;
    scanf("%d", &n);
    long long nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
    }
    */

    // display(nums, n);
    qsort(nums, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%lld ", nums[i]);
    }
    printf("\n");

    return 0;
}
