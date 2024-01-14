#include <vector>
using namespace std;

    // 找第 k 个，k 从 1 开始计算。其下标为 k-1.
    // 可以理解为，去掉 k-1 个数。
    int kth_element_suc(const vector<int>& a, const vector<int>& b, int k) {
        int k0 = k;
        int m = a.size(), n = b.size();
        int i = 0, j = 0; // 去掉若干数后，目前两者的valid元素的起始下标
        while (true) {
            if (i == m) { // 这边已经到了最后元素之后(已被删除光)，可直接算对面的下标
                return b[j + k - 1];
                // 或 return b[k0 - m - 1];
            }
            if (j == n) {
                return a[i + k - 1];
                // 或 return a[k0 - n - 1];
            }
            if (k == 1) { // 已经去掉了 k-1 个数。此时最小的，就是所求。
                return min(a[i], b[j]);
            }

            // 理论情况：去掉 k/2 个，范围是 [i ... i + k/2 - 1] 或 [j ... j + k/2 - 1]. 然后 k -= k/2
            // 但不能超出 a, b 范围，所以与 m-1 或 n-1 最后一个下标比较. 
            // 去掉 [i... ni] 或 [j ... nj] 范围。然后 k -= (ni - i + 1)

            int ni = min(i + k / 2 - 1, m - 1);
            int nj = min(j + k / 2 - 1, n - 1);
            if (a[ni] <= b[nj]) {
                k -= ni - i + 1;
                i = ni + 1;
            } else {
                k -= nj - j + 1;
                j = nj + 1;
            }
        }
    }

    // 去掉 k - 1 个。每次去掉 k/2 个。直到 k == 0。
    // 但 k = 1 时，k/2 为 0，需要特殊处理一下。
    // 上面的官方解法里，k是“第几个”，用来计算去掉多少个，总感觉不太对。
    int kth_element(const vector<int>& a, const vector<int>& b, int k) {
        k--;
        int k0 = k;
        int m = a.size(), n = b.size();
        int i = 0, j = 0; // 去掉若干数后，目前两者的valid元素的起始下标
        while (true) {
            if (i == m) { // 这边已经到了最后元素之后(已被删除光)，可直接算对面的下标
                return b[j + k];
                // 或 return b[k0 - m - 1];
            }
            if (j == n) {
                return a[i + k ];
                // 或 return a[k0 - n - 1];
            }
            if (k == 0) { // 已经去掉了 k-1 个数。此时最小的，就是所求。
                return min(a[i], b[j]);
            }

            // 理论情况：去掉 k/2 个，范围是 [i ... i + k/2 - 1] 或 [j ... j + k/2 - 1]. 然后 k -= k/2
            // 但不能超出 a, b 范围，所以与 m-1 或 n-1 最后一个下标比较. 
            // 去掉 [i... ni] 或 [j ... nj] 范围。然后 k -= (ni - i + 1)

            int ni = k == 1 ? i : min(i + k / 2 - 1, m - 1);
            int nj = k == 1 ? j : min(j + k / 2 - 1, n - 1);
            if (a[ni] <= b[nj]) {
                k -= ni - i + 1;
                i = ni + 1;
            } else {
                k -= nj - j + 1;
                j = nj + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int t = a.size() + b.size();
        if (t % 2 == 1) {
            return kth_element(a, b, (t + 1) / 2);
        } else {
            return double(kth_element(a, b, t / 2) + kth_element(a, b, t / 2 + 1)) / 2.0;
        }

    }

int main() {}