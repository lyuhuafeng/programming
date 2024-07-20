#include <mutex>
#include <condition_variable>
#include <functional> // function()
#include <thread>
#include <iostream>
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
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        _c = 1;
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
    }
};


Foo *foo;
void f1(function<void()> func) { foo->first(func); }
void f2(function<void()> func) { foo->second(func); }
void f3(function<void()> func) { foo->third(func); }

int main() {
    foo = new Foo();
    thread t1(f1, []() { cout << "first " << endl; });
    thread t2(f2, []() { cout << "second " << endl; });
    thread t3(f3, []() { cout << "third " << endl; });
    t1.join();
    t2.join();
    t3.join();
    return 0;
}