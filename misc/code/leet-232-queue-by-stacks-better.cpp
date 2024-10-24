#include <stack>
using namespace std;

// 两个 stack 协作。
// a 负责 push:
//     新元素入队，简单 a.push(x)
// b 负责 pop 和 peek: b 中逆序存放（一部分）元素。
//     第一次 pop/peek 时，把 a 中元素依次弹出并放入 b 中。
//     以后 pop/peek 直接从 b.pop() 或 b.top()。
//     如果某次 pop/peek 时发现 b 空了，就再把 a 中元素都放入 b。

// leet ac 2024.06.19
class MyQueue {
    stack<int> a, b;
public:
    // 把 a 中元素全部放入 b
    void help() {
        while (!a.empty()) {
            b.push(a.top());
            a.pop();
        }
    }

    MyQueue() {}

    void push(int val) {
        a.push(val);
    }

    int pop() {
        if (empty()) {
            return -1; // throw some exception
        }
        if (b.empty()) {
            help();
        }
        // 以上代码，top()、peek() 完全相同。只有下面一点不同。
        int val = b.top();
        b.pop();
        return val;
    }

    int peek() {
        if (empty()) {
            return -1; // throw some exception
        }
        if (b.empty()) {
            help();
        }
        // 以上代码，top()、peek() 完全相同。只有下面一点不同。
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
