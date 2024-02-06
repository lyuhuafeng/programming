#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

    struct pole {
        int i, j; // 位置索引
        int h;   // 虚拟柱的高度
    };

    // 矮的在堆顶，min heap，与缺省的相反，所以比较函数也相反
    bool operator<(const pole &a, const pole &b) {
        return a.h > b.h;
    }
    
    int trapRainWater(vector<vector<int>>& heightMap) {  
        if (heightMap.size() <= 2 || heightMap[0].size() <= 2) {
            return 0;
        }  
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<pole> pq;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    pq.push({i, j, heightMap[i][j]});
                    visited[i][j] = true;
                }
            }
        }

        int res = 0;
        int dirs[] = {-1, 0, 1, 0, -1}; // 这个 trick 有点意思
        while (!pq.empty()) {
            pole p = pq.top();
            pq.pop();            
            for (int k = 0; k < 4; ++k) {
                int i = p.i + dirs[k], j = p.j + dirs[k + 1];
                if (i >= 0 && i < m && j >= 0 && j < n && !visited[i][j]) {
                    if (heightMap[i][j] < p.h) {
                        res += p.h - heightMap[i][j]; 
                    }
                    visited[i][j] = true;
                    pq.push({i, j, max(heightMap[i][j], p.h)});
                }
            }
        }
        
        return res;
    }

int main() {}
