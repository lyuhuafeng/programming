#include <cmath>
using namespace std;

// https://leetcode.cn/problems/sum-of-square-numbers
// leet ac 2024.11.04

// 双指针
// 坑：可能超范围，得用 long
// 坑：两数可能相同，得用 l <= r;

class Solution {
public:
    bool judgeSquareSum(int c) {
        long l = 0, r = sqrt(c);
        while (l <= r) {
            long t = l * l + r * r;
            if (t == (long) c) {
                return true;
            }
            t < (long) c ? l++ : r--;
        }
        return false;
        
    }
};