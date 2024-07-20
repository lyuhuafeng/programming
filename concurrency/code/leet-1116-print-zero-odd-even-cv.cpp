// leet 1116 https://leetcode.cn/problems/print-zero-even-odd

#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class ZeroEvenOdd {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    int turn;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        turn = 0;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [&]{ return turn == 0; });
            printNumber(0);
            turn = (i % 2 == 0) ? 2 : 1;
            ulock.unlock();
            cv.notify_all();
        }        
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [&]{ return turn == 2; });
            printNumber(i);
            turn = 0;
            ulock.unlock();
            cv.notify_all();
        }        
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [&]{ return turn == 1; });
            printNumber(i);
            turn = 0;
            ulock.unlock();
            cv.notify_all();
        }
    }
};

int main() {}