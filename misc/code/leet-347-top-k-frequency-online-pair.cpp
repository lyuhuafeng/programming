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
        // int fr = freq.count(i) == 0 ? 0 : freq[i];
        // todo: 可以再精细点，若 i 以前没出现过
        pair<int, int> cur_key = {freq[i], i};
        freq[i]++;
        pair<int, int> new_key = {freq[i], i};
        if (m.count(cur_key) == 0) {
            // i 以前不在 topk 中：若还不满 k 个，则直接放入 topk；若已满 k 个，要跟 topk 中最小的比较，看是否取代
            if (m.size() < k) {
                m.insert(new_key);
            } else {
                auto last_elem = m.crbegin(); // iterator
                if (last_elem->first < new_key.first) {
                    m.erase(*last_elem);
                    m.insert(new_key);
                }
            }
        } else {
            m.erase(cur_key);
            m.insert(new_key);
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