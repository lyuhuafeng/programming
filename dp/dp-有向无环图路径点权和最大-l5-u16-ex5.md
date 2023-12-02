
[l5-u16-ex5. 小图灵与有向无环图](https://oj.youdao.com/course/37/285/1#/1/14241)

利用邻接表建图，然后枚举计算每一个顶点作为起点的所有路径最大和。实现时可以通过 dfs 遍历该顶点作为起点的所有路径。最后打擂台找到整张图的最大路径和并输出。

状态 dp[i]：i 号顶点为起点的所有路径最大和

状态转移方程
```cpp
// dp[i]：i 号顶点为起点的所有路径最大和

dp[i] = a[i];
for (int j = 0; j < v[i].size(); j++) { // i 指向的所有顶点
    dp[i] = max(dp[i], a[i] + dfs(v[i][j])); // dfs(v[i][j]): 走某个顶点，一直走到头，的最大路径
}
ans = max{dp[i]} // 最终结果
```

完整代码：[dag-longest-path-l5-u16-ex5.cpp](code/dag-longest-path-l5-u16-ex5.cpp)

