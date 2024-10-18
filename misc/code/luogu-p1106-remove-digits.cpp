/*
删数问题
l3-u10-ex4 https://oj.youdao.com/course/12/58/1#/1/8189
P1106 https://www.luogu.com.cn/problem/P1106

删：数位高、数值大的
每次都得从头找，找第一个
每删一个数，要重新验证
若 a[i] > a[i+1]，则删 a[i]
找逆序对 
补思路图

turing ac
luogu ac 2024.03.28
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; // 不超过 250 位
    int k; // 去掉 k 位
    cin >> s >> k;

    for (int i = 0; i < s.size() - 1; ) {
        if (s[i] > s[i + 1] && k > 0) {
            s.erase(s.begin() + i);
            k--;
            if (i > 0) {
                i--;
            } // 避免 231 删两个这种情况
        } else {
            i++;
        }
    }
    int i = 0;
    while (s[i] == '0') {
        i++;
    }
    // i: 第一个不是 0 的位置；i 下标从 0 开始计，i 值恰好也是前导 0 的个数
    s = s.substr(i, s.size() - k - i);
    if (s.empty()) {
        s = "0";
    }
    cout << s;
    return 0;
}