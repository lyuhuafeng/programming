#include <functional>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

// leetcode ac, 
// 但实际上，代码中，在某线程中 lock mutex，但在另一个线程中 unlock。应避免这种操作。

// 基本写法，只用 mutex
class Foo_2 {
private:
    mutex mtx1, mtx2;
public:
    Foo_2() {
        mtx1.lock(), mtx2.lock();
    }

    void first(function<void()> printFirst) {
        printFirst();
        mtx1.unlock();
    }

    void second(function<void()> printSecond) {
        mtx1.lock();
        printSecond();
        mtx1.unlock();
        mtx2.unlock();
    }

    void third(function<void()> printThird) {
        mtx2.lock();
        printThird();
        mtx2.unlock();
    }
};

// 更好写法，用 unique_lock 和 lock_guard 配合 mutex
class Foo {
private:
    mutex mtx_1, mtx_2;
    unique_lock<mutex> ulock1, ulock2;
public:
    Foo() : ulock1(mtx_1, try_to_lock), ulock2(mtx_2, try_to_lock) {}

    void first(function<void()> printFirst) {
        printFirst();
        ulock1.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> guard(mtx_1);
        printSecond();
        ulock2.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> guard(mtx_2);
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