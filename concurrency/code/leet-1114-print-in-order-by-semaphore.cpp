#include <semaphore>
#include <functional>
using namespace std;

// ac 2024.07.16, 本人完全自主实现
// g++ -std=c++20

// acquire: semaphore--
// release: semaphore++

class Foo {
private:
    binary_semaphore sem2{0}, sem3{0};
    
public:
    Foo() {}

    void first(function<void()> printFirst) {
        printFirst();
        sem2.release(); // sem2++，从 0 变为 1
    }

    void second(function<void()> printSecond) {
        sem2.acquire(); // 等待 sem2 从 0 变为 1
        printSecond();
        sem3.release(); // sem3++，从 0 变为 1
    }

    void third(function<void()> printThird) {
        sem3.acquire(); // 等待 sem3 从 0 变为 1
        printThird();
    }
};

int main() {}