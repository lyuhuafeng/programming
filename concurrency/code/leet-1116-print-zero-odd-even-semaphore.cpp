// leet 1116 https://leetcode.cn/problems/print-zero-even-odd

#include <semaphore>
#include <functional>
using namespace std;

// 每个任务（线程）对应一个 semaphore, 用来同步各任务的执行顺序。
// sem_zero 初值设为 1, 这样 sem_zero 可以先执行。另两个初值设为 0，一开始会 block。
// 每个执行完后，会通知另一个继续，以调用相应 sem 的 release() 的方式。

class ZeroEvenOdd {
private:
    int n;
    int count;
    binary_semaphore sem_zero;
    binary_semaphore sem_even;
    binary_semaphore sem_odd;

public:
    ZeroEvenOdd(int n_) : n(n_), count(0), sem_zero(1), sem_even(0), sem_odd(0) {}

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n; i++) {
            sem_zero.acquire();
            // sem_wait(&sem_zero);
            printNumber(0);
            count++;
            if (count % 2 != 0) {
                sem_odd.release();
            } else {
                sem_even.release();
            }
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 0; i < (n/2); i++) {
            sem_even.acquire();
            printNumber(count);
            sem_zero.release();
        }
    }

    void odd(function<void(int)> printNumber) {
        // 奇数执行次数, 使用向上取整
        for (int i = 0; i < (n + 1) / 2; i++) {
            sem_odd.acquire();
            printNumber(count);
            sem_zero.release();
        }
    }
};

