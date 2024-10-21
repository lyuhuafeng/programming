// leet ac 2023.11.02

class Solution {
    // 每个解法是 int[]，记录每行的皇后放在第几列，取值范围 0 ~ n-1
    int total;

    // 判断第 row 行的皇后放在第 col 列行不行，也就是 board[row] =?= col
    // board 里第 0 ~ row-1 个元素是已经放好的皇后，现在判断第 row 个
    boolean is_valid(int[] board, int row, int col) {
        int n = board.length;
        // 检查列是否有皇后互相冲突
        for (int i = 0; i < row; i++) {
            if (board[i] == col) {
                return false;
            }
        }
        // 检查右上方是否有皇后互相冲突。新来的是第k行、第col列。
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i] == j) {
                return false;
            }
        }
        // 检查左上方是否有皇后互相冲突。新来的是第k行、第col列
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i] == j) {
                return false;
            }
        }
        return true;
    }

    // 路径：board 是已经放好的若干行的皇后
    // 选择列表：第 row 行放置皇后的选择
    // 结束条件：row == n (最大范围 + 1），说明棋盘已经放满了（0 ~ n-1 行都放了）
    void backtrack(int[] board, int row) {
        int n = board.length;
        // 触发结束条件
        if (row == n) {
            total++;
            return;
        }
        for (int col = 0; col < n; col++) {
            // 排除不合法选择
            if (!is_valid(board, row, col)) {
                continue;
            }
            board[row] = col; // 做选择；深度往下走一步
            backtrack(board, row + 1);
            // 撤销选择；回溯一步：不用显式操作
        }
    }

    public int totalNQueens(int n) {
        int[] board = new int[n];
        // 不用初始化 board
        // Arrays.fill(board, 0);
        total = 0;
        backtrack(board, 0); // row 参数的初始值为 0：将要放第 0 行的皇后
        return total;
    }
}
