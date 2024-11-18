#include <utility> // swap()
#include <vector>
#include <cassert>
using namespace std;

// Hoare, 分三段，qselect 非递归、递归两种方式，qselect 有或无返回值

// 注意，递归方式下，assert(left <= right)。说明，left 一直小于 right（一旦相等就返回）。
// 注意，这个 assertion 对 qsort 是不成立的。

/*
注意，递归方式一下，if (p == k) { return; } 这句不能少；但非递归方式下，这句就可以不要。
区别在于，递归方式下，若少了这句，会真的用 (k+1, right) 作为 (left, right) 递归调用，可能导致 assertion 出错。
即使去掉了 assertion 这句，逻辑上也不对。
非递归方式下，会被 while 挡住，直接退出，不会出错。

但若判断 if (left >= right) { return; } 就能解决上面这个问题，允许 left > right 输入了。
*/

class Solution {
public:
    // Hoare 三段，Sedgewick 'algorithms' 4th ed. p291
    int partition(vector<int>& a, int l, int r) {
        int key = a[l];
        int i = l, j = r + 1;
        while (true) {
            while (a[++i] > key) { if (i == r) break; } // i 向右找第一个大于等于 k 的。
            while (a[--j] < key) { if (j == l) break; } // j 向左找第一个小于等于 k 的。
            if (i >= j) { break; }
            swap(a[i], a[j]);
        }
        a[l] = a[j], a[j] = key; // 相当于 swap(a[l], a[j])
        return j;
    }

    // 非递归
    void qselect(vector<int>& a, int left, int right, int k) {
        if (left == right) { return; }
        while (left < right) {
            int p = partition(a, left, right);
            if (p == k) { return; } // 这句也可不要
            p > k ? right = p - 1 : left = p + 1;
        }
        assert(left == right); // 从 while 循环退出后，left == right
    }
    // 递归，不允许 left > right 输入
    void qselect(vector<int>& a, int left, int right, int k) {
        assert(left <= right); // 注意，这个 assertion 对 qsort() 不成立
        if (left == right) { return; }
        int p = partition(a, left, right);
        if (p == k) { return; } // 这句必须要，否则下一次递归调用可能出现 left > right 的情况
        if (p > k) {
            qselect(a, left, p - 1, k);
        } else {
            qselect(a, p + 1, right, k);
        }
    }
    // 递归，允许 left > right 输入
    void qselect(vector<int>& a, int left, int right, int k) {
        if (left >= right) { return; }
        int p = partition(a, left, right);
        if (p > k) {
            qselect(a, left, p - 1, k);
        } else {
            qselect(a, p + 1, right, k);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        qselect(nums, 0, nums.size() - 1, k-1);
        return nums[k-1];
    }
};
