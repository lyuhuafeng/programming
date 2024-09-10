#include <future>
#include <functional>
using namespace std;

// ac 2024.07.16
// 注意，future.get() 的作用：blocks until the result is available

class Foo {
private:
    std::promise<void> p2;
    std::promise<void> p3;

public:
    void first(function<void()> printFirst) {
        printFirst();
        p2.set_value();
    }

    void second(function<void()> printSecond) {
        p2.get_future().wait(); // 等（堵塞地）到 p2 被设置了值
        printSecond();
        p3.set_value();
    }

    void third(function<void()> printThird) {
        p3.get_future().wait(); // 等（堵塞地）到 p2 被设置了值
        printThird();
    }
};

int main() {}
