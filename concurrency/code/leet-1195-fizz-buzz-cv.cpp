// leet 1195 https://leetcode.cn/problems/fizz-buzz-multithreaded

#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class FizzBuzz {
private:
    int n;

    int to_print;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n_) : n(n_), to_print(1) {}

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [this]{ return to_print > n || (to_print % 3 == 0 && to_print % 5 != 0); });
            if (to_print > n) {
                break;
            }
            printFizz();
            to_print++;
            ulock.unlock();
            // if (to_print > n) { break; }
            cv.notify_all();
        }        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (true) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [this]{ return to_print > n || (to_print % 3 != 0 && to_print % 5 == 0); });
            if (to_print > n) {
                break;
            }
            printBuzz();
            to_print++;
            ulock.unlock();
            // if (to_print > n) { break; }
            cv.notify_all();
        }        
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [this]{ return to_print > n || to_print % 15 == 0; });
            if (to_print > n) {
                break;
            }
            printFizzBuzz();
            to_print++;
            ulock.unlock();
            // if (to_print > n) { break; }
            cv.notify_all();
        }        
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> ulock(mtx);
            cv.wait(ulock, [this]{ return to_print > n || (to_print % 3 != 0 && to_print % 5 != 0); });
            if (to_print > n) {
                break;
            }
            printNumber(to_print);
            to_print++;
            ulock.unlock();
            // if (to_print > n) { break; }
            cv.notify_all();
        }        
    }
};

int main() {}