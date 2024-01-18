#include <vector>
#include <string>
#include <cstdio>
using namespace std;

void display(unordered_map<string, double>& val, const unordered_map<string, string>& parents) {
    for (auto e : parents) {
        printf(" %s -> %s, %f\n", e.first.c_str(), e.second.c_str(), val[e.first]);
    }
}

string find(unordered_map<string, string>& parents, unordered_map<string, double>& val, const string& u) {
    string p = parents[u];
    if (p == u) {
        return u;
    }
    parents[u] = find(parents, val, p);
    val[u] *= val[p];
    return parents[u];
}
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    unordered_map<string, double> val;     // map<i, value_of_i>
    unordered_map<string, string> parents; // map<i, parent_of_i>, map<分子, 分母>

    for (int i = 0; i < equations.size(); i++) {
        string u = equations[i][0]; // 分子
        string v = equations[i][1]; // 分母
        parents[u] = u;
        parents[v] = v;
        val[u] = 1.0;
        val[v] = 1.0;
    }

    for (int i = 0; i < equations.size(); i++) {
        string u = equations[i][0]; // 分子
        string v = equations[i][1]; // 分母
        string ru = find(parents, val, u), rv = find(parents, val, v);
        if (ru != rv) {
            parents[ru] = rv;
            val[ru] = val[v] * values[i] / val[u];
        }
    }
    // display(val, parents);

    vector<double> ans;
    for (vector<string> q : queries) {
        string u = q[0], v = q[1];
        if (val.count(u) == 0 || val.count(v) == 0) {
            ans.push_back(-1.0);
        } else {
            string ur = find(parents, val, u), vr = find(parents, val, v);
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
// [["a","b"],["b","c"]]
// [2.0,3.0]
// [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// [["a","b"],["b","c"],["bc","cd"]]
// [1.5,2.5,5.0]
// [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
// [["a","b"]]
// [0.5]
// [["a","b"],["b","a"],["a","c"],["x","y"]]