#include <vector>
#include <set>
#include <unordered_map>
#include <utility> // pair
using namespace std;

struct my_cmp {
    bool operator() (const pair<int,int>& a, const pair<int, int>& b) const {
        return a.first > b.first || (a.first == b.first && a.second > b.second);
        // return a.first > b.first; // 导致结果出错，为啥？
    }
};

// 也不能用函数 bool my_cmp() {}，为什么？

// bool operator<(const pair<int,int> &a, const pair<int, int> &b) {
//     return a.first > b.first || (a.first == b.first && a.second > b.second);
// }

class StreamData {
    set<pair<int, int>, my_cmp> m;
    int k;
    unordered_map<int, int> freq;

public:
    StreamData(int k_) : k(k_) {}
    
    void add_num(int i) {
        int fr = freq.count(i) == 0 ? 0 : freq[i];
        pair<int, int> cur_key = {freq[i], i};
        m.erase(cur_key); // 可能删掉，也可能本来 m 中就没有所以没删掉

        freq[i]++;
        pair<int, int> new_key = {freq[i], i};

        if (m.size() < k) {
            // 刚才删掉了 i，或没删掉 i, 但 m 中不够 k 个
            m.insert(new_key);
        } else {
            // m 中有 k 个，说明 m 里本来就没 i（刚才也无从删掉 i）。
            // 需要比较：更新后的 i 的 freq vs. s中最小的
            auto last_elem = m.crbegin(); // iterator
            if (last_elem->first < new_key.first) {
                m.erase(*last_elem);
                m.insert(new_key);
            }
        }
    }

    vector<int> get_topk() {
        vector<int> ans;
        for(auto& i : m) {
            ans.push_back(i.second);
        }
        return ans;
    }
};


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        StreamData s(k);
        for (int i : nums) {
            s.add_num(i);
        }
        vector<int> ans = s.get_topk();
        return ans;
    }
};

int main() {}