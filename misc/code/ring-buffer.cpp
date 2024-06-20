#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// 数据区是 [start, end) 左闭右开区间。浪费一个空间，实际容量是 capacity - 1。
class ring_buffer {
private:
    vector<int> buf;
    uint32_t start;
    uint32_t end;
    int capacity;

    // 两个处理 start、end 下标的 helper
    uint32_t mask(uint32_t i) const { return i & (capacity - 1); }
    uint32_t incr(uint32_t &i) const { return (i = mask(i + 1)); }

public:
    ring_buffer(int c) {
        capacity = c;
        start = 0;
        end = 0;
        buf.resize(c);
    }

    void push_back(int val) {
        buf[end] = val;
        if (incr(end) == start) { // full，则 start++，相当于把 start 原来指向的元素给覆盖了
            incr(start);
        }
    }

    void pop_front() {
        if (empty()) {
            throw out_of_range("Buffer is empty");
        }
        incr(start);
    }

    bool empty() const {
        return end == start;
    }

    bool full() const {
        return mask(end + 1) == start;
    }

    int size() const {
        // return (end >= start) ? (end - start) : (capacity - (start - end));
        return mask(end - start);
    }

    void print_buffer() const {
        for (uint32_t i = start; i != end; incr(i)) {
            printf("%d ", buf[i]);
        }
        printf("\nbuffer size: %d\n", size());
    }
};

int main() {
    ring_buffer buffer(8);
    for (int i = 1; i <= 8; ++i) {
        buffer.push_back(i);
    }
    buffer.print_buffer();

    for (int i = 0; i < 4; ++i) {
        buffer.pop_front();
    }
    buffer.print_buffer();

    for (int i = 9; i <= 22; ++i) {
        buffer.push_back(i);
    }
    buffer.print_buffer();

    return 0;
}
