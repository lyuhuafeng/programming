#include <semaphore>
#include <functional>
using namespace std;

// ac 2024.07.16, 本人完全自主实现
// g++ -std=c++20

// acquire: semaphore--
// release: semaphore++

class Foo {
private:
    binary_semaphore smph1{0}, smph2{0};
    
public:
    Foo() {}

    void first(function<void()> printFirst) {
        printFirst();
        smph1.release(); // smph1++，从 0 变为 1
    }

    void second(function<void()> printSecond) {
        smph1.acquire(); // 等待 smph1 从 0 变为 1
        printSecond();
        smph2.release(); // smph2++，从 0 变为 1
    }

    void third(function<void()> printThird) {
        smph2.acquire(); // 等待 smph2 从 0 变为 1
        printThird();
    }
};

int main() {}