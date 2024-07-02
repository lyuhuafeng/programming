#include <vector>
using namespace std;

class MyCircularDeque {
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
    MyCircularDeque(int k) : capacity(k + 1), start(0), end(0) {
        buf.resize(k + 1);
    }
    
    bool insertFront(int value) {
        if (isFull()) { return false; }
        buf[decr(start)] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) { return false; }
        buf[end] = value;
        incr(end);
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) { return false; }
        incr(start);
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) { return false; }
        decr(end);
        return true;
    }
    
    int getFront() {
        return isEmpty() ? -1 : buf[start];
    }
    
    int getRear() {
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
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */