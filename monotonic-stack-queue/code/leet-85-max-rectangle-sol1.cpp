#include <vector>
#include <stack>
using namespace std;

    int largestRectangleArea(vector<int> &heights) {
        heights.push_back(-1); // 只用尾哨兵，不用首哨兵
        unsigned long n = heights.size();
        int res = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) { // > 或 >= 都行
                int ti = st.top();
                int h = heights[ti];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                res = max(res, h * w);
            }
            st.push(i);
        }
        return res;
    }    
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) {
            return 0;
        }
        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int max_area = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == '1') {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            max_area = max(max_area, largestRectangleArea(heights));
        }
        return max_area;
    }

int main() {}