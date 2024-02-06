#include <vector>
#include <algorithm> // max()
#include <queue>
#include <cstdio>
using namespace std;

    struct pole {
        int idx; // 位置索引
        int h;   // 虚拟柱的高度
    };

    // 矮的在堆顶，min heap，与缺省的相反，所以比较函数也相反
    bool operator<(const pole &a, const pole &b) {
        return a.h > b.h;
    }

    int trap(vector<int>& height) {
        vector<int> dirs = { -1, 1 };

        int n = height.size();
        vector<bool> visited(n, false);
        visited[0] = true, visited[n - 1] = true;

        priority_queue<pole> pq;
        pq.push({0, height[0]});
        pq.push({n - 1, height[n - 1]});
            printf("push: {%d, %d}\n", 0, height[0]);
            printf("push: {%d, %d}\n", n-1, height[n-1]);

        int ans = 0;
        while (!pq.empty()) {
            pole p = pq.top();
            pq.pop();
            printf("pop: {%d, %d}\n", p.idx, p.h);

            // 看看左右两边的情况
            for (int d : dirs) {
                int pos = p.idx + d;
                if (pos >= 0 && pos <= n - 1 && !visited[pos]) {
                    if (height[pos] < p.h) {
                        ans += p.h - height[pos];
                        printf("_add: %d (compare: %d, %d)\n", p.h - height[pos], pos, height[pos]);
                    }
                    pq.push({pos, max(height[pos], p.h)});
                    printf("push: {%d, %d}\n", pos, max(height[pos], p.h));
                    visited[pos] = true;
                }
            }            
        }
        return ans;
    }

int main() {
    vector<int> height = {5,3,1,10,8,6,9,2};
    // {0,1,0,2,1,0,1,3,2,1,2,1};
    int ans = trap(height);
    printf("%d\n", ans);
    return 0;
}