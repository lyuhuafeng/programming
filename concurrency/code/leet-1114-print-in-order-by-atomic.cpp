#include <atomic>
#include <thread>
using namespace std;

// 写法一
// ac 2024.07.16

class Foo {
    std::atomic<int> turn = 1;
public:
    Foo() {}

    void first(function<void()> printFirst) {
        while (turn != 1) { this_thread::yield(); }
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        turn++;
    }

    void second(function<void()> printSecond) {
        while (turn != 2) { this_thread::yield(); }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        turn++;
    }

    void third(function<void()> printThird) {
        while (turn != 3) { this_thread::yield(); }
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};


// 写法二：貌似更「正规」些。
//    - 用 turn.load() != 1 代替 turn != 1
//    - 用 turn.fetch_add(1) 代替 turn++
//    - 用 turn.store(1) 代替 turn = 1
// 或：
//   私有成员只声明，不初始化；在构造函数中初始化。
//     std::atomic<int> turn;
//     Foo() : turn(1) {}
//     Foo() { turn.store(1); }
// ac 2024.07.16

class Foo {
private:
    std::atomic<int> turn{1};
public:
    Foo() {}

    void first(function<void()> printFirst) {
        while (turn.load() != 1) { this_thread::yield(); }
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        turn.fetch_add(1);
    }

    void second(function<void()> printSecond) {
        while (turn.load() != 2) { this_thread::yield(); }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        turn.fetch_add(1);
    }

    void third(function<void()> printThird) {
        while (turn.load() != 3) { this_thread::yield(); }
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

int main() {}