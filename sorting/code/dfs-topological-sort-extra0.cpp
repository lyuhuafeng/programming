#include <iostream>
#include <vector>
using namespace std;

void add_edge(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
}

void visit_vertex(int v, const vector<int> adj[], bool visited[], vector<int>& res) {
    visited[v] = true; // 标记当前节点为 visited
    cout << "  util: " << v << endl;

    for (int i : adj[v]) {
        if (!visited[i]) {
            cout << "  util iterate: " << i << endl;
            visit_vertex(i, adj, visited, res);
        } else {
            cout << "  util skipped iterate: " << i << endl;
        }
    }
    
    res.push_back(v); // 访问完 v 的所有邻接顶点后，再放入 v 自己
    cout << "  util pushed " << v << endl;
}

// 传入 n 是节点数，不是 adj 数组大小
vector<int> topological_sort(int n, vector<int> adj[]) {
    // 引入虚拟顶点，编号 0
    for (int i = 1; i <= n; i++) {
        add_edge(adj, 0, i);
    }

    bool visited[n + 1]; // 顶点是否访问过
    memset(visited, 0, sizeof visited); // 初始化为 全false

    vector<int> res;
    visit_vertex(0, adj, visited, res);
    res.pop_back(); // 去掉虚拟顶点 0
    reverse(res.begin(), res.end()); // 逆序，即为所求顺序
    return res;
}

int main() {
    int n = 9; // 9个顶点，编号从1开始
    vector<int> adj[n + 1]; // 顶点的邻接表

    add_edge(adj, 1, 8);
    add_edge(adj, 1, 3);
    add_edge(adj, 2, 3);
    add_edge(adj, 2, 5);
    add_edge(adj, 8, 9);
    add_edge(adj, 3, 4);
    add_edge(adj, 5, 4);
    add_edge(adj, 9, 7);
    add_edge(adj, 4, 7);
    add_edge(adj, 4, 6);
    add_edge(adj, 5, 6);

    // 传入 n 是节点数，不是 adj 数组大小
    vector<int> order = topological_sort(n, adj);
    cout << "result (one of):" << endl;
    for (int v : order) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
