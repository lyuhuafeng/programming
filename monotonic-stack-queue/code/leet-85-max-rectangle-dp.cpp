#include <vector>
#include <algorithm> // max(), min()
using namespace std;

    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) {
            return 0;
        }
        int cols = matrix[0].size();
        vector<int> heights(cols);
        vector<int> l(cols, -1), r(cols, cols); // left smaller, right smaller

        int max_area = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == '1') {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }

            int p = -1; // 上次出现 0 的位置
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == '1') { // 与上次出现 0 的位置比较
                    l[j] = max(l[j], p);
                } else {
                    // 当前是 0 代表当前高度是 0，所以初始化为 -1，防止对下次循环的影响
                    l[j] = -1;
                    p = j; // 更新 0 的位置
                }
            }
            // 右边，同理
            p = cols;
            for (int j = cols - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    r[j] = min(r[j], p);
                } else {
                    r[j] = cols;
                    p = j;
                }
            }

            for (int j = cols - 1; j >= 0; j--) {
                max_area = max(max_area, (r[j] - l[j] - 1) * heights[j]);
            }
        }
        return max_area;
    }

int main() {}