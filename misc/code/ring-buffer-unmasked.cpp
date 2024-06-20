#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// 数据区是 [start, end) 左闭右开区间。不浪费空间，实际容量就是 capacity。
class ring_buffer {
private:
    vector<int> buf;
    uint32_t start;
    uint32_t end;
    int capacity;

    // 处理 start、end 下标的 helper
    uint32_t mask(uint32_t i) const { return i & (capacity - 1); } // same

public:
    ring_buffer(int c) {
        capacity = c;
        start = 0;
        end = 0;
        buf.resize(c);
    }

    void push_back(int val) {
        buf[mask(end++)] = val;
        if (size() >= capacity) {
            start = end - capacity;
        }
    }

    int pop_front() {
        if (empty()) {
            throw out_of_range("buffer is empty");
        }
        return buf[mask(start++)];
    }

    bool empty() const {
        return end == start;
    }

    bool full() const {
        return end - start == capacity;
    }

    int size() const {
        return end - start;
    }

    void print_buffer() const {
        for (uint32_t i = start; i != end; i++) {
            printf("%d ", buf[mask(i)]);
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
