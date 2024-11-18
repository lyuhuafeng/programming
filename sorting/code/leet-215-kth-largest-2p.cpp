#include <utility> // swap()
#include <vector>
#include <cassert>
using namespace std;

// Hoare, 分两段，qselect 有或无返回值，qselect 非递归或递归

class Solution {
public:
    // Hoare 两段 [l, p] 和 [p+1, r]
    // impl 1，来自 wikipedia https://en.wikipedia.org/wiki/Quicksort 和 mit「算法导论」书
    int partition(vector<int>& a, int l, int r) {
        long key = a[l];
        int i = l - 1, j = r + 1;
        while (true) {
            do { i++; } while (a[i] > key); // 这两句，谁先谁后都可以
            do { j--; } while (a[j] < key); // 这两句，谁先谁后都可以
            if (i >= j) { return j; }
            swap(a[i], a[j]);
        }
    }

// qselect() 无返回值的情况
    // 非递归
    void qselect(vector<int>& a, int left, int right, int k) {
        if (left == right) { return; }
        while (left < right) {
            int p = partition(a, left, right);
            p >= k ? right = p : left = p + 1;
        }
        assert(left == right); // 从 while 循环退出后，left == right
    }

    // 递归，不会出现 left > right 的情况。因为 p == k 时下次递归调用的参数是 p 而不是 p+1
    void qselect(vector<int>& a, int left, int right, int k) {
        assert(left <= right);
        if (left == right) { return; }
        int p = partition(a, left, right);
        if (p >= k) {
            qselect(a, left, p, k);
        } else {
            qselect(a, p + 1, right, k);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        qselect(nums, 0, nums.size() - 1, k-1);
        return nums[k-1];
    }




// qselect() 有返回值的情况
    // 非递归
    int qselect(vector<int>& a, int left, int right, int k) {
        if (left == right) { return a[k]; }
        while (left < right) {
            int p = partition(a, left, right);
            p >= k ? right = p : left = p + 1;
        }
        return a[left];
    }
    // 递归
    int qselect(vector<int>& a, int left, int right, int k) {
        assert(left <= right);
        if (left == right) { return a[left]; }
        int p = partition(a, left, right);
        if (p >= k) {
            return qselect(a, left, p, k);
        } else {
            return qselect(a, p + 1, right, k);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        return qselect(nums, 0, nums.size() - 1, k-1);
    }

};