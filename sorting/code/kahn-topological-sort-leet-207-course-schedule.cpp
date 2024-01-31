#include <vector>
#include <queue>
using namespace std;

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // prerequisites[i] = [ai, bi]: ai 必须先修 bi. 邻接关系：ai <- bi
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

int main() {
    vector<vector<int>> prerequisites = {{2, 1}, {3, 2}, {2, 4}};
    canFinish(5, prerequisites); // 4 个顶点，编号从 1 开始。canFinish() 要求编号从 0 开始，所以这里参数是 5.
    prerequisites = {{1, 0}, {2, 1}, {3, 2}, {4, 2}, {1, 3}};
    canFinish(5, prerequisites); // 5 个顶点，编号从 0 开始。
    return 0;
}