#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0); // 每个顶点的 in-degree
        unordered_map<int, unordered_set<int>> nexts; // 每个顶点可到达的顶点列表
        for (const vector<int> & e : prerequisites) {
            indegree[e[0]]++;
            nexts[e[1]].insert(e[0]);
        } // 统计每个顶点的 in-degree 和 可到达顶点列表

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        } // in-degree 为 0 的所有顶点，放入 queue

        vector<int> ans;
        int visited_vertex = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            visited_vertex++;
            ans.push_back(v); // 就多了这一句
            for (int u : nexts[v]) {
                indegree[u]--;
                if (indegree[u] == 0) {
                    q.push(u);
                }
            }
        }
        if (visited_vertex != numCourses) {
            ans.clear();
        }
        return ans;
    }

int main() {}