#include <vector>
#include <utility> // pair
#include <algorithm> // max()
#include <cstdio>
using namespace std;

class Solution {
public:

    // entry_lt() 作为类的成员函数，需要加 static，否则后面 lower_bound() 调用报错：
    //   reference to non-static member function must be called
    // 或者把 entry_lt() 定义在类之外，就不用加 static 了。
    //
    // 因是 pair，故不能重载 operator<(pair, int)。若是结构体，则可以。
    static bool entry_lt(const pair<int, int> &a, int key) {
        return a.first < key;
    }

    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> v; // pair<value, index>，「下标逆序」的元素序列
        v.push_back({nums[n - 1], n - 1});
        printf("push(%d,%d)\n", nums[n - 1], n - 1);
        int max_width = 0;
        for (int i = n - 2; i >= 0; i--) { // 逆序遍历 i，也方便逆序放入元素序列
            // 在「下标逆序」序列中，找第一个「值 >= 当前值」的元素
            int idx = lower_bound(v.begin(), v.end(), nums[i], entry_lt) - v.begin();
            if (idx < v.size()) { // 找到：该元素的下标 j，与当前元素下标 i 构成一个「坡」。该元素自身不用放入「序列」中。
                int j = v[idx].second;
                max_width = max(max_width, j - i);
                printf("i:%d, val:%d, v.size:%zu, idx:%d, width:%d\n", i, nums[i], v.size(), idx, j - i);
            } else { // 没找到：当前元素值比序列中所有元素都大。将其放入「序列」中。
                v.push_back({nums[i], i});
                printf("i:%d, val:%d, v.size:%zu, idx:%d. push(%d,%d)\n", i, nums[i], v.size(), idx, nums[i], i);
            }
        }
        return max_width;
    }
};

int main() {
    vector<int> nums = {6,0,8,2,1,5};
    // vector<int> nums = {9,8,1,0,1,9,4,0,4,1};
    Solution sol;
    int max_width = sol.maxWidthRamp(nums);
    printf("%d\n", max_width);
    return 0;
}