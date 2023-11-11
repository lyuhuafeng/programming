# Floyd-Marshall 最短路算法

## 综述

动态规划的思路

to add pic from docx

代码中，为省空间，可直接在原来空间上迭代，这样空间可降至二维。

## 代码
```cpp
int n = 10; // 顶点数
int dist[n][n];
for each (i, j):
    dist[i][j] = inf // 初始化: 任两顶点间距离为inf
for each vertex v:
    dist[v][v] = 0 // 自己到自己，距离为0
for each edge (u,v):
    dist[u][v] = w(u, v)  // weight of edge (u,v)

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int t = dist[i][k] + dist[k][j];
            if (dist[i][j] > t) {
                dist[i][j] = t;
            }
        }
    }
}
```


十字计算法

另一种理解思路

重建整个path

With negative cycles



