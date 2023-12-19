#include <vector>
#include <string>
#include <cstdio>
using namespace std;

void display(unordered_map<string, double>& val, const unordered_map<string, string>& parents) {
    for (auto e : parents) {
        printf(" %s -> %s, %f\n", e.first.c_str(), e.second.c_str(), val[e.first]);
    }
}

vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    unordered_map<string, double> val;     // map<i, value_of_i>
    unordered_map<string, string> parents; // map<i, parent_of_i>

    for (int i = 0; i < equations.size(); i++) {
        string u = equations[i][0]; // 分子
        string v = equations[i][1]; // 分母
        if (parents.count(u) == 0 && parents.count(v) == 0) { // u, v 均未处理过：以分母 v 为 root
            parents[v] = v;
            parents[u] = v;
            val[v] = 1.0; // 分母值为 1.0
            val[u] = values[i];
        } else if (parents.count(u) == 0) { // 只有 u (分子) 未处理过
            parents[u] = parents[v];
            val[u] = val[v] * values[i];
        } else if (parents.count(v) == 0) { // 只有 v (分母) 未处理过
            parents[v] = parents[u];
            val[v] = val[u] / values[i];
        } else { // u, v 均处理过
            string ur = parents[u], vr = parents[v];
            if (ur != vr) { // u,v 均处理过，且在不同的树
                double factor = val[u] / values[i] / val[v];
                // 遍历 v 所在的树，都直接挂到 ur 上
                for (auto e : parents) {
                    if (e.second == vr) {
                        val[e.first] *= factor;
                        parents[e.first] = ur;
                    }
                }
            } else { // ur == vr: u, v 均处理过，且在同一棵树：不应该出现这种情况
                // does nothing.
            }
        }
        // display(val, parents);
    }

    vector<double> ans;
    for (vector<string> q : queries) {
        string u = q[0], v = q[1];
        if (val.count(u) == 0 || val.count(v) == 0) {
            ans.push_back(-1.0);
        } else {
            string ur = parents[u], vr = parents[v];
            if (ur != vr) {
                ans.push_back(-1.0);
            } else {
                ans.push_back(val[u] / val[v]);
            }
        }
    }
    return ans;
}

int main() {
    vector<vector<string>> equations = {{"a","b"},{"e","f"},{"b","e"}};
    vector<double> values = {3.4,1.4,2.3};
    vector<vector<string>> queries = {{"b","a"},{"a","f"},{"f","f"},{"e","e"},{"c","c"},{"a","c"},{"f","e"}};
    vector<double> ans = calcEquation(equations, values, queries);
    for (double val : ans) {
        printf("%f, ", val);
    }
    printf("\n");
    return 0;
}
