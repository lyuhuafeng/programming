
[347. 前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements)

top k

- 法一，用类似 insertion sort 的方法，维护一个长度最多为 k 的数组
- 法二，用 heap，经典方法
- 法三，online 流式处理，因为要更新 topk 里已经记录的 freq，故用 set 代替 heap
- 法四，online 流式处理，法一的变种 <font color=red>todo</font>
- trie

流式处理
  - 法三的分布式版本，
  - Count-Min Sketch 算法代替 hashmap 
  - Lossy Counting
  - SpaceSaving 原始论文 "Efficient Computation of Frequent and Top-k Elements in Data Streams"
ref:
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/heavy-hitters.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/frequency-estimation.html
  - https://www.cnblogs.com/fxjwind/p/3289221.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/data-stream-sampling.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/cardinality-estimation.html

# 法一，用类似 binary insertion sort 的方法，维护一个长度最多为 k 的数组

```cpp
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m; // <元素, 出现次数>
        for (int i : nums) { m[i]++; }

        vector<int> res(k);
        int llen = 0; // last+1. 最大为 k
        for (auto& e : m) {
            if (llen == 0) {
                res[llen++] = e.first;
                continue;
            }
            // 找第一个 < e.occurs 的 i; 从 i 到 end 右移；e 放在 i 处
            int l = 0, r = llen;
            while (l < r) {
                int p = l + (r - l) / 2;
                if (m[res[p]] < e.second) {
                    r = p;
                } else {
                    l = p + 1;
                }
            }

            int lend; // l_end
            if (llen == k) {
                if (l >= k) { continue; }
                lend = k - 1 - 1; // 第 k 个（下标 k-1）扔掉
            } else {
                lend = llen - 1;
                llen++;
            }
            for (int j = lend; j >= l; j--) {
                res[j + 1] = res[j];
            }
            res[l] = e.first;
        }
        return res;
    }
```

# 法二，用 heap，经典方法

```cpp
    struct myitem { int val; int occurs; };
    bool operator<(const myitem &a, const myitem &b) {
        return a.occurs > b.occurs;
    }
    // k largest -> 来个更大的，最小的被删 -> 最小的在 heap 顶 -> min-heap，与缺省的相反
    vector<int> topKFrequent_heap(vector<int>& nums, int k) {
        unordered_map<int, int> m; // <num, 出现次数>
        for (int i : nums) { m[i]++; }

        priority_queue<myitem> q;
        for (auto& e : m) {
            if (q.size() < k) {
                q.push({e.first, e.second});
            } else {
                if (e.second > q.top().occurs) {
                    q.pop();
                    q.push({e.first, e.second});
                }
            }
        }
        vector<int> ans;
        while (!q.empty()) {
            ans.push_back(q.top().val);
            q.pop();
        }
        return ans;
    }
```

# 法三，online 流式处理，因为要更新 topk 里已经记录的 freq，故用 set 代替 heap

直观逻辑，[用 struct 的代码](code/leet-347-top-k-frequency-online-struct.cpp)、[用 pair 的代码](code/leet-347-top-k-frequency-online-pair.cpp)

稍微有点不太直观的逻辑，[用 pair 的代码](code/leet-347-top-k-frequency-online-pair-sol2.cpp)