// n 皇后问题
// leet ac 2023.11.02

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 每个解法是 vector<int>，记录每行的皇后放在第几列，取值范围 0 ~ n-1
// res: 所有解法的集合
vector<vector<int>> res;

// 是否可以在 board[row][col] 放置皇后？
// 若 k = board.size()，board 里是第 0 ~ k-1 行的皇后位置。
// 判断第 k 行放在第 col 列行不行
bool is_valid(vector<int>& board, int col, int n) {
    int k = board.size();
    // 检查列是否有皇后互相冲突
    if (find(board.begin(), board.end(), col) != board.end()) {
        return false;
    }
    // 检查右上方是否有皇后互相冲突。新来的是第 k 行、第 col 列。
    for (int i = k - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i] == j) {
            return false;
        }
    }
    // 检查左上方是否有皇后互相冲突。新来的是第 k 行、第 col 列
    for (int i = k - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i] == j) {
            return false;
        }
    }
    return true;
}

// 路径：board 是已经放好的若干行的皇后
// 选择列表：下一行放置皇后的选择
// 结束条件：board.size() == n，说明棋盘放满了
void backtrack(vector<int>& board, int n) {
    // 触发结束条件
    if (board.size() == n) {
        res.push_back(board);
        return;
    }
    for (int col = 0; col < n; col++) {
        // 排除不合法选择
        if (!is_valid(board, col, n)) {
            continue;
        }
        board.push_back(col); // 做选择；深度往下走一步
        backtrack(board, n);
        board.pop_back(); // 撤销选择；回溯一步
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<int> board; // 路径初始为空：一步都没走
    backtrack(board, n);
    vector<vector<string>> result;
    for (vector<int> r : res) {
        vector<string> r2;
        for (int col : r) {
            string row(n, '.');
            row[col] = 'Q';
            r2.push_back(row);
        }
        result.push_back(r2);
    }
    return result;
}

int main() {
    int n = 5;
    vector<vector<string>> result = solveNQueens(n);
    return 0;
}
