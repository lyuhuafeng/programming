#include <vector>
#include <cstdio>
#include <iostream>
#include <bitset>
using namespace std;


    int dp(int x, const vector<vector<int>>& f) {
        int t = x;
        vector<int> nums;
        while (t != 0) {
            nums.push_back(t % 10);
            t /= 10;
        }
        int n = nums.size();
        if (n <= 1) {
            return x + 1; // [0, 9]
        }
        // 位数与 x 相同（res1 + res2）
        int ans = 0;
        for (int i = n - 1, s = 0; i >= 0; i--) {
            int cur = nums[i], cnt = 0;
            for (int j = cur - 1; j >= 0; j--) {
                if (i == n - 1 && j == 0) { // 最高位不能为0
                    continue;
                }
                if (((s >> j) & 1) == 0) { // s 第 j 位为 0：数字 j 未被使用
                    cnt++;
                }
            }
            if (i == 0) {
                // 当前是最低位，不用再考虑更低的位。
                // 「最后再加一个」，不在这里做，在后面确认 cur 未被高位使用后再加。
                ans += cnt;
            } else {
                // 当前是第 i 位，因下标从 0 开始，故恰好还剩 i 位。
                // 已经使用了 n-i 个数字，则剩下的 i 位的最高位，可选数字有 `a = 10-(n-i)` 个。
                // 共 i 位要选，则最低位可选数字有 b = a-i+1 个。共 f[b][a] 种。
                int a = 10 - (n - i), b = a - i + 1;
                ans += cnt * f[b][a];
            }
            if (((s >> cur) & 1) == 1) { // s 第 cur 位为 1：数字 cur 已被使用
                break;
            }
            if (i == 0) {
                ans++; // 已确认 cur 没被高位使用，故可「最后再加一个」
            }
            s |= (1 << cur); // 设置：s 第 cur 位为 1；数字 cur 已被使用
        }
        // 位数比 x 少的情况。每位数不受上限限制，可选 0-9 任意。
        ans += 10; // 一位数，包括 0
        // for (int i = 1; i <= n - 2; i++) {
        //     // printf("    fff:%d\n", 9 * f[9-i+1][9]);
        //     ans += 9 * f[9-(n-2)+1][9];
        // }
        
        for (int i = 2, cur = 9; i <= n - 1; i++) { // 枚举 i 位数, 2 .. n-1 
            cur *= (10 - i + 1);
            ans += cur;
        }
        return ans;
    }
    int countNumbersWithUniqueDigits(int n) {
        vector<vector<int>> f(10, vector<int>(10));
        for (int i = 1; i <= 9; i++) {
            int cur = 1;
            for (int j = i; j <= 9; j++) {
                cur *= j;
                f[i][j] = cur;
            }
        }

        return dp((int)pow(10, n) - 1, f);
    }

int main() {
    int n = 2;
    int cnt = countNumbersWithUniqueDigits(n);
    printf("%d\n", cnt);
    return 0;
}
