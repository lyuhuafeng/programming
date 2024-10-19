# 广度优先搜索 bfs

大概框架如下：

```
    读取题目给出的初始位置或状态 s0
    if (s0 就是终点位置、成功状态) {
        输出步数或路径
        结束
    }

    定义 queue<status> q 和 visited 数组。
    初始化 visited 数组，所有元素值均初始化为「未访问过」

    q.push(s0)，并标记 s0 为「访问过」
    while (q 不空) {
        取出 q 头元素 s
        遍历 s 能走到的每一个状态或位置 si。对每个 si {
            if (si 成功) { 输出步数或路径；结束 }
            if (si 已被访问过) { 跳过 si，不把 si 放入 q }
            q.push(si)，并标记 si 为「访问过」，更新步数或路径
        }
    }
    循环结束，说明从 s0 出发不能到达终点位置；输出「失败」并结束
```

几个要点：
* 出发状态、位置放入 q 前，最好先判断是否已「成功结束」（出发位置恰好就是目的地），然后再放入 q。
* 不要把状态、位置重复放入 q。这是 visited 数组的目的。为此，每把一个状态、位置 s 放入 queue，就要把在 visited 数组里把 s 标记为「访问过」。
* 每走到一个新状态、新位置，先判断是否「成功结束」，再判断是否「访问过」，然后再放入 queue。而不是每次从 queue 头取出一个状态、位置后判断是否「成功」或「访问过」。这样可以防止无用功。

若用数组或 vector 模拟 queue，<font color="red">to add later</font>

两种类型
* 到目标位置，至少需要多少步。
* 到目标位置的完整路径。

题目
- [马的遍历](马的遍历.md)
- [分油](分油.md)
- [`luogu p1135.` 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：[bfs 解法](code/luogu-p1135-elevator-bfs.cpp)，[从 dijkstra 改的 bfs 解法](code/luogu-p1135-elevator-bfs-sol2.cpp)