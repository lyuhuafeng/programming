#include <vector>
#include <set>
using namespace std;

// leet ac 2024.10.19

/*
概率最大，而不是距离最短。probs[] 初始化为 0.0；relax 时是乘法。
queue 中，按 prob 从到小排序，而不是按 dist 从小到大排序。
用 set 而不是 priority_queue。自定义 operator<()。
push 前根据 prob 判断，不用判断 visited；pop 后既不用判断 prob，也不用判断 visited。
单个重点，找到后（pop 时）即返回。
*/
struct edge {
    int from; // 其实无用
    int to;
    double prob;
};
struct vertex {
    int id;
    double prob;
};
bool operator<(const vertex& a, const vertex& b) {
    return tie(a.prob, a.id) > tie(b.prob, b.id);
}
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, 
                int start_node, int end_node) {
        if (start_node == end_node) {
            return 1.0;
        }

        // n 个顶点，编号从 0 到 n-1，恰好用数组存邻接表，adj[i] 是第 i 个顶点的邻接表
        vector<edge> adj[n];
        for (int i = 0; i < edges.size(); i++) {
            int from = edges[i][0];
            int to = edges[i][1];
            double prob = succProb[i];
            adj[from].push_back({from, to, prob});
            adj[to].push_back({to, from, prob});
        }

        vector<double> probs(n, 0.0);
        set<vertex> q;

        probs[start_node] = 1.0;
        q.insert({start_node, probs[start_node]});

        while (!q.empty()) {
            int u = q.begin()->id;
            q.erase(q.begin());
            if (u == end_node) {
                return probs[end_node];
            }

            for (edge& e : adj[u]) {
                int v = e.to;
                double p = e.prob;
                if (probs[u] * e.prob > probs[v]) {
                    if (q.count({v, probs[v]}) > 0) {
                        q.erase({v, probs[v]});
                    }
                    probs[v] = probs[u] * e.prob;
                    q.insert({v, probs[v]});
                }
            }
        }
        return 0;
    }
};

int main() {
    int n = 3;
    vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
    vector<double> succProb = {0.5, 0.5, 0.3};
    int start_node = 0;
    int end_node = 2;
    double ans = Solution().maxProbability(n, edges, succProb, start_node, end_node);
    printf("%f\n", ans);
}