// https://leetcode.cn/contest/tianchi2022/problems/ev2bru/
// 2024.05.28 ac

#include <cstdio>
#include <vector>
#include <unordered_map>
using namespace std;

// 类似 leet 316。remain[] 与 316 一样，表示每个元素在后续还剩多少个；增加了 instack[] 表示每个元素在栈内已经有多少个。
// 可以发现，instack[] 就是推广了的 visited[]，visited[] 就是只有 0、1 两个值的 instack[]。
// 316 中判断 if (visited[i] == true) 相当于这里的 if (instack[i] >= limit)
// 316 中判断 remain[st.back()] > 0 相当于这里的 remain[st.back()] + instack[st.back()] > limit

    vector<int> arrangeBookshelf(vector<int>& order, int limit) {
        unordered_map<int, int> remain, instack; // 某个 bid，后续还有多少个、栈中已经有多少个
        for (int bid : order) { remain[bid]++; }
        for (auto i : remain) { instack[i.first] = 0; }

        vector<int> st;
        for (int bid : order) {
            remain[bid]--; // 不管 bid 是否放入栈，它「后面还有几次」数量都减一
            if (instack[bid] >= limit) {
                continue;
            }
            while (!st.empty() && bid < st.back() && remain[st.back()] + instack[st.back()] > limit) {
                instack[st.back()]--;
                st.pop_back();
            }
            st.push_back(bid);
            instack[bid]++;
        }
        return st;
    }

int main() {
    vector<int>order = {2,1,2,2,1,3,3,1,3,3};
    int limit = 2;
    vector<int> res = arrangeBookshelf(order, limit);
    for (int bid : res) {
        printf("%d ", bid);
    }
    printf("\n");
    return 0;
}
