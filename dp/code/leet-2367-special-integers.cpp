#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;


    int countSpecialNumbers(int x) {
        string s = to_string(x);
        int n = s.length(), memo[n][1 << 10];
        fill_n(&memo[0][0], sizeof memo / sizeof(int), -1); // -1 表示没有计算过
        printf("__ s:%s, n:%d\n", s.c_str(), n);

        // is_limit: 当前位 第 i 位，是否受「<= s[i]」限制
        // is_num:
        //     true:  i 前面的数位填了数字；则当前位不可跳过；（至少 i-1 是填了；再往前有可能没填？）
        //     false: i 前面的数位未填数字；则当前位可以跳过；（所有位都没填？）
        //            （可以跳过，不是一定跳过。代码里是执行了跳过、不跳过两个分支）
        function<int(int, int, bool, bool)> f = [&](int i, int mask, bool is_limit, bool is_num) -> int {
            printf("f: i:%d, mask:%d, is_limited:%d, is_num:%d\n", i, mask, is_limit, is_num);
            if (i == n) { // 最低位之后
                return is_num ? 1 : 0; // is_num 为 true 表示得到了一个合法数字
            }

            //  isLimit 的时候不能使用缓存数据
            if (!is_limit && memo[i][mask] != -1) {
                return memo[i][mask];
            }
            int res = 0; // 方案数量
            if (!is_num) {// 可以跳过当前数位：跳过。
                printf("__ i:%d, skip current pos.\n", i);
                res = f(i + 1, mask, false, false);
            }
            // 可以跳过当前位、但不跳过；或不可跳过当前位：当前位需要填个数字。枚举当前位可选数字
            int min_d = is_num ? 0 : 1;
            int max_d = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
            printf("__ i:%d, enumerate d: %d -> %d\n", i, min_d, max_d);
            for (int d = min_d; d <= max_d; ++d) { // 枚举要填入的数字 d
                if ((mask >> d & 1) == 0) { // d 不在 mask 中
                    res += f(i + 1, mask | (1 << d), is_limit && d == max_d, true);
                    // is_num == true: i 位填了数字，则 i+1 位也必须填
                    // is_limit: 若 i 位不受限制，可以随便填，则 i+1 位更不用受
                    //     若 i 位受限制，如 8467，当前第i=1位(s[1]=4)，
                    // 则若本位填了4(最大可能值)，则第 i+1 位需考虑限制，最多到6；
                    // 若 第 i+1 位不受限制，随便填，比如填了 8, 则 848x > 8467。
                }
            }
            // 写缓存貌似不用管 is_limit 的值
            memo[i][mask] = res;
            return res; // 方案数量
        };

        return f(0, 0, true, false);
    }

int main() {
    int x = 58;
    int ans = countSpecialNumbers(x);
    printf("%d\n", ans);
    return 0;
}
