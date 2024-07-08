#include <stack>
using namespace std;

// 两个 stack 协作。
// a 负责 push:
//     新元素入队，简单 a.push(x)
// b 负责 pop 和 peek: b 中逆序存放（一部分）元素。
//     第一次 pop/peek 时，把 a 中元素依次弹出并放入 b 中。
//     以后 pop/peek 直接从 b.pop() 或 b.top()。
//     如果某次 pop/peek 时发现 b 空了，就再把 a 中元素都放入 b。

class MyQueue {
    stack<int> a, b;
public:
    MyQueue() {}

    void push(int val) {
        a.push(val);
    }
    
    int pop() {
        if (b.empty() && a.empty()) {
            // throw some exception
            return -1;
        }
        if (b.empty()) {
            while (!a.empty()) {
                b.push(a.top());
                a.pop();
            }
        }
        // 以上代码，top()、peek() 完全相同。这有下面一点不同。
        int val = b.top();
        b.pop();
        return val;
    }
    
    int peek() {
        if (b.empty() && a.empty()) {
            // throw some exception
            return -1;
        }
        if (b.empty()) {
            while (!a.empty()) {
                b.push(a.top());
                a.pop();
            }
        }
        // 以上代码，top()、peek() 完全相同。这有下面一点不同。
        return b.top();
    }
    
    bool empty() {
        return a.empty() && b.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */