#include <stack>
using namespace std;

// 两个 stack，一个 a 用来存放所有元素，另一个 b 作为 helper。
// push(): 简单放入 a 顶。
// pop(): 要得到 a 的栈底元素。为此先把压在上面的元素都弹出，在 b 中暂存；得到 buttom 元素后，再从 b 中弹出并放回。
// peek(): 跟 pop() 差不多。

class MyQueue {
    stack<int> a;
public:
    MyQueue() {}
    
    void push(int x) {
        a.push(x);
    }
    
    int pop() {
        stack<int> b;
        while (!a.empty()) {
            b.push(a.top());
            a.pop();
        }
        int val = b.top();
        b.pop();
        while (!b.empty()) {
            a.push(b.top());
            b.pop();
        }
        return val;
    }
    
    int peek() {
        stack<int> b;
        while (!a.empty()) {
            b.push(a.top());
            a.pop();
        }
        int val = b.top();
        while (!b.empty()) {
            a.push(b.top());
            b.pop();
        }
        return val;

    }
    
    bool empty() {
        return a.empty();

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
