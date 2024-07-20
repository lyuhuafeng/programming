// leet 1115: https://leetcode.cn/problems/print-foobar-alternately

#include <mutex>
#include <condition_variable>
using namespace std;

class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool foo_done;

public:
    FooBar(int n) {
        this->n = n;
        foo_done = false;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [&]{ return !foo_done; });
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            foo_done = true;
            ulock.unlock();
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [&]{ return foo_done; });
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            foo_done = false;
            ulock.unlock();
            cv.notify_one();
        }
    }
};

int main() {}
