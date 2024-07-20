#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct freq_item {
    int val;
    int freq;

    // set 中不能有重复元素，所以 freq 相等时还要用 val 再比较
    bool operator<(const freq_item &b) const {
        return freq < b.freq || (freq == b.freq && val < b.val);
        // return tie(freq, val) < tie(b.freq, b.val); // 更简洁直观的写法，用 tie()
    }
};

class StreamData {
    set<freq_item> q; // topk 的 <val, freq>。从小到大排序。
    int k;
    unordered_map<int, int> freq; // 每个数的 <val, freq>

public:
    StreamData(int k_) : k(k_) {}
    
    void add_num(int i) {
        // int fr = freq.count(i) == 0 ? 0 : freq[i];
        // todo: 可以再精细点，若 i 以前没出现过
        freq_item cur_key = {i, freq[i]};
        freq[i]++;
        freq_item new_key = {i, freq[i]};
        if (q.count(cur_key) == 0) {
            // i 以前不在 topk 中：若还不满 k 个，则直接放入 topk；若已满 k 个，要跟 topk 中最小的比较，看是否取代
            if (q.size() < k) {
                q.insert(new_key);
            } else {
                if (q.begin()->freq < new_key.freq) {
                    q.erase(q.begin());
                    q.insert(new_key);
                }
            }
        } else {
            // i 已经在 topk 里，且出现次数又加一，肯定还继续在 topk 中：在 topk 中更新它
            q.erase(cur_key);
            q.insert(new_key);
        }
    }

    vector<int> get_topk() {
        vector<int> ans;
        for(auto& i : q) {
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