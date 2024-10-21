#include <vector>
#include <algorithm>
using namespace std;

/*
  船运载能力 小 ---> 大
  需要的天数 多 ---> 少， >days, =days, <days 三部分
  找第一个 <= d 的天数 
*/

// leet ac 2024.10.20

class Solution {
public:
    // true: <= days, false: > days 
    bool f(vector<int>& weights, int cap, int days) {
        int cnt = 0;
        int sum = 0;
        for (int w : weights) {
            if (sum + w <= cap) {
                sum += w;
            } else {
                cnt++;
                if (cnt > days) {
                    return false;
                }
                sum = w;
            }
        }
        cnt++;
        return cnt <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int maxw = weights[0], sumw = 0;
        for (int w : weights) {
            maxw = max(maxw, w);
            sumw += w;
        }
        int l = maxw, r = sumw + 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            f(weights, m, days) ? r = m : l = m + 1;
        }
        return l;        
    }
};

int main() {}