#include <cstdio>
#include <vector>
using namespace std;

vector<int> max_items; // 记录放入哪些物品能得到最大 value
int max_value = 0; // 记录最大 value

// 第i件物品已选择（放入或不放入），入参的 value、weight 已更新为第 i 件放入或不放入后的值。
// 放之前检查是否会超重。
// 一开头，就检查目前状态是否更好，然后检查是否到达终点（所有物品都选择过了 i==n）
void dfs(int w[], int v[], int n, int W, int i, vector<int>& items, int weight, int value) {
    if (value > max_value) {
        max_value = value;
        max_items = items;
    }
    if (i == n) {
        return;
    }
    // 放第 i+1 个
    if (weight + w[i + 1] <= W) {
        items.push_back(i + 1); // df: 放入第 i+1 个
        // dfs()的三个参数: i+1, weight + w[i+1], value + v[i+1]: 放入第 i+1 个后的结果
        dfs(w, v, n, W, i + 1, items, weight + w[i + 1], value + v[i + 1]);
        items.pop_back(); // 回溯：去掉第 i+1 个
    }
    // 不放第i+1个
    dfs(w, v, n, W, i + 1, items, weight, value);
}
int main() {
    int n;  // 共多少件物品
    int W;  // 购物车容量
    scanf("%d%d", &n, &W);
    
    int w[n + 1], v[n + 1]; // 下标都从1开始
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }
    vector<int> items;
    dfs(w, v, n, W, 0, items, 0, 0);
    printf("max_value: %d\n", max_value);
    for (int i = 0; i < max_items.size(); i++) {
        printf("%d ", max_items[i]);
    }
    printf("\n");
    return 0;
}