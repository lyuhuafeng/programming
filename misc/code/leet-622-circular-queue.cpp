#include <vector>
using namespace std;

class MyCircularQueue {
private:
    int capacity;
    vector<int> buf;
    int start, end;

    int to_idx(int i) {
        if (i < 0) { return i + capacity; }
        if (i >= capacity) { return i - capacity; }
        return i;
    }
    int incr(int &i) {
        return (i = to_idx(i + 1));
    }
    int decr(int &i) {
        return (i = to_idx(i - 1));
    }
public:
    // 按题意，实际容量 k，则 capacity = k + 1
    MyCircularQueue(int k) : capacity(k + 1), start(0), end(0) {
        buf.resize(k + 1);
    }
    
    bool enQueue(int value) {
        if (isFull()) { return false; }
        buf[end] = value;
        incr(end);
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) { return false; }
        incr(start);
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : buf[start];
    }
    
    int Rear() {
        return isEmpty() ? -1 : buf[to_idx(end - 1)];
    }
    
    bool isEmpty() {
        return start == end;
    }
    
    bool isFull() {
        return to_idx(end + 1) == start;
    }
};

int main() {}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */