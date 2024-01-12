#include <vector>
#include <queue>
using namespace std;

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        for (const vector<int> & e : prerequisites) {
            indegree[e[0]]++;
        } // 统计每个顶点的 in-degree

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        } // in-degree 为 0 的所有顶点，放入 queue

        int visited_vertex = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            visited_vertex++;
            for (const vector<int> & e : prerequisites) {
                if (e[1] == v) {
                    indegree[e[0]]--;
                    if (indegree[e[0]] == 0) {
                        q.push(e[0]);
                    }
                }
            }
        }
        int ans = (visited_vertex == numCourses);
        return ans;
    }

int main() {}