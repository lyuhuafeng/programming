// leet 1195 https://leetcode.cn/problems/fizz-buzz-multithreaded

#include <functional>
#include <semaphore>
using namespace std;

// 使用 semaphore, 保证同时只有一个打印方法在运行
// 每个打印完后, 递增当前数字, 并根据其值判断要唤醒哪个打印方法继续执行（通过调用对应的 semaphore 的 V 原语、release() 函数）
// 每个线程都等待对应的 semaphore
// 
// 如何让第一个 number() 先运行起来？
// 法一、二、三：所有 semaphore 都初始化为 0。
// 法一：单独搞个 starter 函数，里面 turn() 一次，使 number() 运行起来。但对本题来说，没有 starter 函数，故此法不行。
// 法二：number() 循环里判断，若是第一次运行就不用 acquire() 了。
// 法三：法二的另一种写法。
// 法四，最佳，把 sem_number 初始化为 1，number() 写法跟 fizz/buzz 等完全一样，不用特殊处理第一次。
// 特殊情况, 打印完了所有数字, 要唤醒所有的等待线程, 使它们退出循环

class FizzBuzz {
private:
    int n;

    int to_print;
    binary_semaphore sem_number;
    binary_semaphore sem_both;
    binary_semaphore sem_fizz;
    binary_semaphore sem_buzz;

    // 递增当前 to_print, 并根据其值 post 对应的 semaphore, 以唤醒相应的线程继续执行
    void turn() {
        to_print++;
        // 特殊情况, 打印完了所有数字, 要唤醒所有的等待线程, 使它们退出循环
        if (to_print > n) {
            sem_fizz.release();
            sem_buzz.release();
            sem_both.release();
            sem_number.release();
        } else {
            if (to_print % 15 == 0) {
                sem_both.release();
            } else if (to_print % 3 == 0) {
                sem_fizz.release();
            } else if (to_print % 5 == 0) {
                sem_buzz.release();
            } else {
                sem_number.release();
            }
        }
    }

public:
    FizzBuzz(int n_): n(n_), to_print(1), sem_both(0), sem_fizz(0), sem_buzz(0), sem_number(1) {}

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (true) {
            sem_fizz.acquire();
            if (to_print > n) {
                break;
            }
            printFizz();
            turn();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (true) {
            sem_buzz.acquire();
            if (to_print > n) {
                break;
            }
            printBuzz();
            turn();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            sem_both.acquire();
            if (to_print > n) {
                break;
            }
            printFizzBuzz();
            turn();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    // 写法四，最佳。代码与 fizz/buzz 等完全一样，不用特殊处理第一次。但 sem_number 要初始化为 1。
    void number(function<void(int)> printNumber) {
        while (true) {
            sem_number.acquire();
            if (to_print > n) {
                break;
            }
            printNumber(to_print);
            turn();
        }
    }

    // 写法二，sem_number 初始化为 0。第一次单独判断一下。
    void number_sol2(function<void(int)> printNumber) {
        while (true) {
            if (to_print > 1) {
                sem_number.acquire();
            }
            if (to_print > n) {
                break;
            }
            printNumber(to_print);
            turn();
        }
    }

    // 写法三，是写法二的小变种。把 acquire 挪到最后，与 fizz/buzz 等相反，逻辑上要多想一下。
    // sem_number 与写法二一样，初始化为 0。
    void number_sol3(function<void(int)> printNumber) {
        while (true) {
            if (to_print > n) {
                break;
            }
            printNumber(to_print);
            turn();
            sem_number.acquire();
        }
    }
};

int main() {}