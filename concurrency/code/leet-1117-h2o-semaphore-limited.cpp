// leet 1117 https://leetcode.cn/problems/building-h2o

#include <mutex>
#include <semaphore>
#include <functional>
#include <thread>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

/*
用 semaphore，固定顺序输出 HHO，其实不符合题意，但可练习 semaphore 的使用。

各用一个 semaphore 控制 h 和 o。sem_h 显然最大值为 2。自然认为 sem_o 的最大值为 1，但不对。
为何？
hydrogen 线程每输出一个 H，sem_o++，若 sem_o == 2，说明已经输出了两个 H，该输出 O 了。
若最大值为 1，无法跟 h 达到 2:1 的比例。

则，每次要输出 O，要先 sem_o.acquire(2)。但 c++ 中无法一次 acquire 两个，只能做两次 acquire(1)。
这里有个坑。两个独立的 acquire(1)，则先拿一个，block 住，但第二个被 release 出来后，可能被另一个 oxygen 线程 acquire 了，
导致两个线程都堵住。
解法：把这两个 acquire() 作为一个整体。为此，用 mutex 来保护他们。
*/

class H2O {
private:
    mutex mtx; // 保护 sem_o 的两个 acquire() 作为一个整体完成
    counting_semaphore<2> sem_h, sem_o;

public:
    H2O() : sem_h(2), sem_o(0) {}

    void hydrogen(function<void()> releaseHydrogen) {
        sem_h.acquire();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        sem_o.release();
    }

    void oxygen(function<void()> releaseOxygen) {
        { // 两个 acquire() 作为一个整体完成
            lock_guard<mutex> guard(mtx);
            sem_o.acquire();
            sem_o.acquire();
        }
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        sem_h.release(2);
    }
};

void releaseHydrogen() {
    printf("H");
    fflush(stdout);
}
void releaseOxygen() {
    printf("O");
    fflush(stdout);
}
int main() {
    // string s = "HOH";
    // string s = "OOHHHH";
    string s = "HHHHHHHHHHOHHOHHHHOOHHHOOOOHHOOHOHHHHHOOHOHHHOOOOOOHHHHHHHHH";

    vector<thread> threads;
    H2O h2o;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == 'H') {
            threads.emplace_back(&H2O::hydrogen, &h2o, releaseHydrogen);
        } else if (c == 'O') {
            threads.emplace_back(&H2O::oxygen, &h2o, releaseOxygen);
        }
    }
    for (thread& t : threads) {
        t.join();
    }
}