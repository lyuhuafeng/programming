import java.util.Arrays; // Arrays.toString()

// 方法二，并查集，标准做法
// 每个顶点先初始化为单独的 CC
// 然后遍历每条 edge
// - 若两顶点不在同一 CC，则合并这两个 CC；
// - 若两顶点已在同一 CC，则有问题：增加此 edge 将导致 cycle！

class Solution {
    int find(int[] parents, int i) {
        if (parents[i] == i) {
            return i;
        }
        parents[i] = find(parents, parents[i]);
        return parents[i];
    }
    void unite(int[] parents, int[] rank, int u, int v) {
        int ru = find(parents, u), rv = find(parents, v);
        if (ru == rv) {
            return;
        }
        if (rank[ru] <= rank[rv]) {
            parents[ru] = rv;
            if (rank[ru] == rank[rv]) {
                rank[rv]++;
            }
        } else {
            parents[rv] = ru;
        }
    }
    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        int[] parents = new int[n + 1];
        int[] rank = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            parents[i] = i;
            rank[i] = 1;
        }
        for (int i = 0; i < n; i++) {
            int u = edges[i][0], v = edges[i][1];
            if (find(parents, u) == find(parents, v)) {
                return new int[]{u, v};
            }
            unite(parents, rank, u, v);
        }
        return new int[]{}; // shouldn't be here
    }

    public static void main(String[] args) {
        int[][] edges = {{1, 2}, {1, 3}, {2, 3}};
        int[] ans = new Solution().findRedundantConnection(edges);
        System.out.println(Arrays.toString(ans));
    }
}

