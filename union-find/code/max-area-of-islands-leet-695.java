class Solution {

    int maxArea = 0; // 所求最大面积
    public int maxAreaOfIsland(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        UnionFind uf = new UnionFind(grid);
        for (int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int k = i * n + j;
                if (grid[i][j] == 1) { // 以下两行，如果右侧或下侧能够合并到当前岛中，合并之
                    if (j < n - 1 && grid[i][j + 1] == 1) {
                        uf.union(k, k + 1);
                    }
                    if (i < m - 1 && grid[i + 1][j] == 1) {
                        uf.union(k, k + n);
                    }
                }
            }
        }
        return maxArea;
    }

    private class UnionFind{
        private int[] parents;
        private int[] size;

        public UnionFind(int[][] grid) {
            int m = grid.length, n = grid[0].length;
            this.parents = new int[m * n];
            this.size = new int[m * n];
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == 1) { // 针对单格岛，赋值parents[k]和size[k]
                        int k = i * n + j;
                        parents[k] = k;
                        size[k] = 1;
                        if (maxArea != 1) {
                            maxArea = 1;
                        } // 有单格岛时更新max=1
                    }
                }
            }
        }
        // 带路径压缩的查找
        public int find(int k) {
            if (parents[k] == k) {
                return k;
            }
            return parents[k] = find(parents[k]);
        }
        // 按大小求并
        public void union(int i, int j) {
            int ri = find(i), rj = find(j);
            if (ri != rj) {
                if (size[rj] <= size[ri]) { // y所在集合大小小于等于x所在集合时，rj挂到ri上
                    parents[rj] = ri;
                    size[ri] += size[rj];
                    maxArea = Math.max(maxArea, size[ri]); // 更新 maxArea
                } else { // ri 挂到 rj 上
                    parents[ri] = rj;
                    size[rj] += size[ri];
                    maxArea = Math.max(maxArea, size[rj]); // 更新 maxArea
                }
            }
        }
    }
}

