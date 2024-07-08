#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct freq_item {
    int val;
    int freq;
};

bool operator<(const freq_item &a, const freq_item &b) {
    return a.freq > b.freq || (a.freq == b.freq && a.val > b.val);
}

class StreamData {
    set<freq_item> m;
    int k;
    unordered_map<int, int> freq;

public:
    StreamData(int k_) : k(k_) {}
    
    void add_num(int i) {
        // int fr = freq.count(i) == 0 ? 0 : freq[i];
        // todo: 可以再精细点，若 i 以前没出现过
        freq_item cur_key = {i, freq[i]};
        freq[i]++;
        freq_item new_key = {i, freq[i]};
        if (m.count(cur_key) == 0) {
            // i 以前不在 topk 中：若还不满 k 个，则直接放入 topk；若已满 k 个，要跟 topk 中最小的比较，看是否取代
            if (m.size() < k) {
                m.insert(new_key);
            } else {
                auto last_elem = m.crbegin(); // iterator
                if (last_elem->freq < new_key.freq) {
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
            ans.push_back(i.val);
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