#include <vector>
#include <algorithm>
using namespace std;

    struct edge {
        int u, v;
        int effort;
        bool operator<(const edge& o) {
            return effort < o.effort;
        }
    };

    int find(int parents[], int i) {
        if (parents[i] == i) {
            return i;
        }
        return (parents[i] = find(parents, parents[i]));
    }
    void unite(int parents[], int rank[], int i, int j) {
        int ri = find(parents, i), rj = find(parents, j);
        if (ri != rj) {
            if (rank[ri] >= rank[rj]) {
                parents[rj] = ri;
                if (rank[ri] == rank[rj]) {
                    rank[ri]++;
                }
            } else {
                parents[ri] = rj;
            }
        }
    }

    int minimumEffortPath(vector<vector<int>>& h) {
        int m = h.size();
        if (m == 0) {
            return -1;
        }
        int n = h[0].size();
        if (n == 0) {
            return -1;
        }
        if (m == 1 && n == 1) {
            return 0;
        }
        vector<edge> edges;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int idx = i * n + j;
                if (j < n - 1) {
                    edges.push_back({idx, idx + 1, abs(h[i][j] - h[i][j + 1])});
                }
                if (i < m - 1) {
                    edges.push_back({idx, idx + n, abs(h[i][j] - h[i + 1][j])});
                }
            }
        }
        sort(edges.begin(), edges.end());

        int len = m * n;
        int parents[len], rank[len];
        for (int i = 0; i < len; i++) {
            parents[i] = i;
            rank[i] = 1;
        }
        for (edge e : edges) {
            unite(parents, rank, e.u, e.v);
            if (find(parents, 0) == find(parents, len - 1)) {
                return e.effort;
            }
        }
        return -1;
    }

