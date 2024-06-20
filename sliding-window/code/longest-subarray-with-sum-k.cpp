// 给定一个由正整数组成的无序数组 arr 和一个整数 K ，在所有 arr 子数组中找到累加和等于 K ，并且长度最长的子数组，返回该长度。
// 示例：
// 输入：arr = [3,2,1,3,3,1,1,1,1,1,1,2,2,2], K = 6
// 输出：6
// 解释：组合方式有多种：
//   3 + 2 + 1 = 6
//   2 + 1 + 3 = 6
//   3 + 3 = 6
//   3 + 1 + 1 + 1 = 6
//   1 + 1 + 1 + 1 + 1 + 1 = 6
//   ......
// 最长子数组为 6 个 1 时，因此返回 6 。

#include <vector>
#include <algorithm>
using namespace std;

// [l, r) 范围，r 不包含在内
void display(const vector<int> &arr, int l, int r) {
    for (int i = l; i < r; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// while 循环一开始，sum 是已经算好的、当前窗口的「和」，不需要先右移窗口便边界。
// while 内用 if 而不是用 while。
int max_length(const vector<int> &arr, int k) {
    int l = 0, r = 0;
    int sum = 0;
    int maxl = 0;
    while (r <= arr.size()) {
        // printf("____l:%d, r:%d, sum:%d ", l, r-1, sum); display(arr, l, r);
        if (sum == k) {
            maxl = max(maxl, r - l);
            printf("l:%d, r:%d, len:%d: ", l, r, r - l);
            display(arr, l, r);
            sum -= arr[l];
            l++;
        } else if (sum < k) {
            sum += arr[r];
            r++;
        } else if (sum > k) {
            sum -= arr[l];
            l++;
        }
    //     if (sum == k) {
    //         maxl = max(maxl, r - l);
    //         printf("l:%d, r:%d, len:%d: ", l, r, r - l);
    //         for (int i = l; i < r; i++) {
    //             printf("%d ", arr[i]);
    //         }
    //         printf("\n");
    //         sum -= arr[l];
    //         l++;
    //     } else if (sum > k){
    //         sum -= arr[l];
    //         l++;
    //     }
    }

    return maxl;
}

int main() {
    vector<int> arr = {3,2,1,3,3,1,1,1,1,1,1,2,2,2};
    int k = 6;
    display(arr, 0, arr.size());
    int maxl = max_length(arr, k);
    printf("maxl:%d\n", maxl);
    return 0;
}
