#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;


// 法一，用 vector 存 next greaters，用 find() 在 nums2 中找
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector p(m, -1); // nums2 的 next greaters。与法二不同 p[idx] = next-greater-val
        stack<int> st; // 单调下降栈，存下标
        for (int i = 0; i < m; i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                p[st.top()] = nums2[i]; // 与法二不同
                st.pop();
            }
            st.push(i);
        }
        vector<int> res;
        for (int val : nums1) {
            int j = find(nums2.begin(), nums2.end(), val) - nums2.begin(); // 与法二不同
            res.push_back(p[j]);
        }
        return res;
    }

// 法二，用 unordered_map 存 next greaters，不需 find()
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int m = nums2.size();
        unordered_map<int, int> p; // nums2 的 next greaters. 与法一不同 <val, next-greater-val>
        stack<int> st; // 单调下降栈，存下标
        for (int i = 0; i < m; i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                p[nums2[st.top()]] = nums2[i]; // 与法一不同
                st.pop();
            }
            st.push(i);
        }
        vector<int> res;
        for (int val : nums1) {
            res.push_back(p.count(val) == 0 ? -1 : p[val]); // 与法一不同
        }
        return res;
    }

int main() {}