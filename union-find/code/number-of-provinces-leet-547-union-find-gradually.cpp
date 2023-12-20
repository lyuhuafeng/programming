#include <vector>
using namespace std;

class Solution {

private:
    class union_find {
    private:
        vector<int> parents; // 链表, 若 parents[i] == i 则 i 为树的 root
        vector<int> rank; // rank[i]: i 作为 root 的树的 rank
        int merged_count = 0;
    public:
        int disjoint_count = 0;

    public:
        union_find(const vector<vector<int>> & isConnected) {
            int n = isConnected.size();
            parents.resize(n, -1); // parent 都初始化为 -1，表示“无 parent”、“尚未加入并查集”
            rank.resize(n); // rank 不用初始化；只需在加入时更新 root 的 rank
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (isConnected[i][j] == 1) {
                        unite(i, j);
                    }
                }
            }
            disjoint_count = n - merged_count;
            // for (int i = 0; i < n; i++) {
            //     printf("%d -> %d\n", i, parents[i]);
            // }
        }
        // 找 i 所在的树的 root，并顺便压缩路径
        int find(int i) {
            if (parents[i] < 0) {
                return parents[i];
            } // 以上：尚未加入并查集，返回 -1。普通并查集实现没有这种情况。
            if (parents[i] == i) {
                return i;
            }
            parents[i] = find(parents[i]);
            return parents[i];
        }
        // 合并 i、j 所在的树。rank 小的，挂到另外一棵树的 root 上。
        void unite(int i, int j) {
            int ir = find(i), jr = find(j); // 二者所在树的 root
            if (ir < 0 && jr < 0) { // 两者都还不在并查集内。无向，谁当 root 都行，选 i 当 root。
                merged_count++;
                parents[i] = i; parents[j] = i;
                rank[i] = 2;
            } else if (ir < 0) { // j 已在并查集内，i 不在并查集内。将 i 挂到 j 所在树
                merged_count++;
                parents[i] = jr;
                // rank[jr] 不用变
            } else if (jr < 0) {
                merged_count++;
                parents[j] = ir;
                // rank[ir] 不用变
            } else { // 两者都已经在并查集内。
                if (ir != jr) { // 两个 root 不同，是不同的树，需要合并
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
        }
    };

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        union_find uf(isConnected);
        return uf.disjoint_count;
    }
};

int main() {
    vector<vector<int>> is_connected = {{1,1,1},{1,1,1},{1,1,1}};
    Solution sol;
    int ans = sol.findCircleNum(is_connected);
    printf("ans:%d\n", ans);
    return 0;
}
