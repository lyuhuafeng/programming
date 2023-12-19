#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

// 改进方法 1
// 每个连通分量用一个 set 存储。多个 set 放在一个 vector 里。
// visited[i] 表示 i 是否已访问过，true/false，用在 bfs 中。
// 每个节点都 bfs 完成后，连通分量的数量为 v.size()
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<bool> visited(n, false); // 都没访问过
    vector<unordered_set<int>> v;
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        unordered_set<int> s;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int k = q.front();
            q.pop();
            for (int j = 0; j < n; j++) {
                if (isConnected[k][j] > 0 and !visited[j]) {
                    s.insert(j);
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
        v.push_back(s);
    }
    return v.size();
}

// 改进方法 2
// 不用 set 及其 vector 记录各连通分量了。
// bool visited[i] 改为 int prov[i]，表示 i 属于哪个连通分量。若 i=0 表示还没访问过。用在 bfs 中。
// 用 cnt 记录发现了几个连通分量，省去了 set、vector<set> 以及最后 v.size()
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<int> prov(n, 0); // prov[i]: i属于哪个省
    int cnt = 0; // 从1开始
    for (int i = 0; i < n; i++) {
        if (prov[i] > 0) {
            continue;
        }
        cnt++;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int k = q.front();
            q.pop();
            for (int j = 0; j < n; j++) {
                if (isConnected[k][j] > 0 and prov[j] == 0) {
                    prov[j] = cnt;
                    q.push(j);
                }
            }
        }
    }
    return cnt;
}
