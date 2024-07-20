// leet 1117 https://leetcode.cn/problems/building-h2o

#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class H2O {
private:
    int num_h, num_o;
    mutex mtx;
    condition_variable cv;

    void test_h2o_complete() {
        if (num_h == 2 && num_o == 1) {
            num_h = 0, num_o = 0;
        }
    }
public:
    H2O() : num_h(0), num_o(0) {}

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> ulock(mtx);
        cv.wait(ulock, [&]{ return num_h < 2; });
        num_h++;
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        test_h2o_complete();
        ulock.unlock();
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> ulock(mtx);
        cv.wait(ulock, [&]{ return num_o < 1; });
        num_o++;
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        test_h2o_complete();
        ulock.unlock();
        cv.notify_all();
    }
};
