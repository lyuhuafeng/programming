#include <mutex>
#include <condition_variable>
#include <functional> // function()
using namespace std;

// ac 2024.07.16

class Foo {
private:
    std::mutex _mtx;
    std::condition_variable _cv;
    int _c;

public:
    Foo() {
        _c = 0;
        _cv.notify_all();
    }

    void first(function<void()> printFirst) {
        std::unique_lock<std::mutex> ulock(_mtx);
        _cv.wait(ulock, [this]{return _c == 0;});
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        _c = 1;
        ulock.unlock();
        _cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex> ulock(_mtx);
        _cv.wait(ulock, [this]{return _c == 1;});
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        _c = 2;
        ulock.unlock();
        _cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex> ulock(_mtx);
        _cv.wait(ulock, [this]{return _c == 2;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        // _c = 0;
        // ulock.unlock();
        // _cv.notify_all();
    }
};

int main() {}
