
```cpp
class MedianFinder {
public:
    priority_queue<int> ql; // 左半部分，max heap, 比 mean 小的，一半或多一个
    priority_queue<int, vector<int>, greater<int>> qr; // 右半部分，min heap, 比 mean 大的，一半或少一个
    
    // ------------------- --------------------
    // (small)     (great) (small)      (great)
    //         (left half) (right half)
    //          (max heap) (min heap)
    //                 top top
    // ql 的 size 可能与 qr 的相等，也可能多一个

    MedianFinder() {}
    void addNum(int num) {
        // 这两段的逻辑是一样的：想放入 b，实际上先放入 a，（a 内自己调整），再把 a 的 top 取出放入 b。
        if (ql.size() != qr.size()) { ////////////////////// 1: 改为 ==
            // 原来二者不等长，需放入 qr 中。
            // 用堆的自身调整替换了比较大小。
            ql.push(num);
            qr.push(ql.top());
            ql.pop();
        } else {
            // 原来二者等长，需放入 ql 中。
            // 用堆的自身调整替换了比较大小。
            qr.push(num);
            ql.push(qr.top());
            qr.pop();
        }
    }
    
    double findMedian() {
        return ql.size() != qr.size() ? ql.top() : (ql.top() + qr.top()) / 2.0f; ////////////////// 2 改为 qr.top()
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

若设定 ql.size() <= qr.size()，则只要做两处改动，如上面注释所示。
