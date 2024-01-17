#include <vector>
using namespace std;

    class union_find {
    private:
        vector<int> parents; // 链表, 若 parents[i] == i 则 i 为树的 root
        vector<int> rank; // rank[i]: 以 i 为 root 的树的 rank
        int merged_count = 0;
    public:
        int disjoint_count = 0;

    public:
        union_find(const vector<vector<int>> & isConnected) {
            int n = isConnected.size(); // 共有多少节点
            for (int i = 0; i < n; i++) {
                parents.push_back(i);
                rank.push_back(1);
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (isConnected[i][j] == 1) {
                        unite(i, j);
                    }
                }
            }
            disjoint_count = n - merged_count;
        }
        // 找 i 所在的树的 root，并顺便压缩路径
        int find(int i) {
            if (parents[i] == i) {
                return i;
            }
            parents[i] = find(parents[i]);
            return parents[i];
        }
        // 合并 i、j 所在的树。rank 小的，挂到另外一棵树的 root 上。
        void unite(int i, int j) {
            int ir = find(i), jr = find(j); // 二者所在树的 root
            if (ir != jr) { // 两个 root 不同，是不同的树，才需要合并
                merged_count++;
                // rank 小的，挂到另外一棵树的 root 上
                if (rank[ir] <= rank[jr]) {
                    parents[ir] = jr;
                    if (rank[ir] == rank[jr]) {
                        rank[jr]++; // 只有当两树 rank 相等时，合并后新树 rank++
                    }
                } else {
                    parents[jr] = ir;
                }
            }
        }
    };

    // find() 的另一种实现，非递归
    int find2(vector<int>& parents, int i) {
        vector<int> path;
        while (parents[i] != i) {
            path.push_back(i);
            i = parents[i];
        }
        // now: i is the root
        for (int j : path) {
            parents[j] = i;
        }
        return i;
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        union_find uf(isConnected);
        return uf.disjoint_count;
    }

int main() {}