#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder {
public:
    priority_queue<int> ql; // 左半部分，max heap, 比 mean 小的，一半或一半多一个
    priority_queue<int, vector<int>, greater<int>> qr; // 右半部分，min heap, 比 mean 大的，half + 1
    // ------------------- --------------------
    // (small)     (great) (small)      (great)
    //         (left half) (right half)
    //          (max heap) (min heap)
    //                 top top
    // ql 的 size 可能与 qr 的相等，也可能多一个

    MedianFinder() {}
    
    void addNum(int num) {
        if (ql.empty()) {
            ql.push(num);
        } else if (qr.empty()) {
            if (num < ql.top()) {
                int k = ql.top();
                ql.pop();
                qr.push(k);
                ql.push(num);
            } else {
                qr.push(num);
            }
        } else if (ql.top() <= num && num <= qr.top()) {
            if (ql.size() == qr.size()) {
                ql.push(num);
            } else {
                qr.push(num);
            }
        } else if (num > qr.top()) {
            if (ql.size() == qr.size()) {
                int k = qr.top();
                qr.pop();
                ql.push(k);
            }
            qr.push(num);
        } else { // num < ql.top()
            if (ql.size() > qr.size()) {
                int k = ql.top();
                ql.pop();
                qr.push(k);
            }
            ql.push(num);
        }
        // printf("num:%d, queues: %d -> %d\n", num, ql.top(), qr.top());

    }
    
    double findMedian() {
        // printf("ql.size:%zu, qr.size:%zu\n", ql.size(), qr.size());
        if (ql.size() == 0) {
            return 0.0;
        } else if (qr.size() == 0) {
            return ql.top();
        }
        return (ql.size() > qr.size()) ? ql.top() : ((qr.top() + ql.top()) / 2.0);
    }
};

int main() {
    int nums[] = { -1, -2, -3, -4, -5 };
    // int nums[] = { 1, 2, 3 };
    MedianFinder obj;
    for (int i : nums) {
        obj.addNum(i);
        double m = obj.findMedian();
        printf("%.1f\n", m);
    }
    return 0;
}
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
