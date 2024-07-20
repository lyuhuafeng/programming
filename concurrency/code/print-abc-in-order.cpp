#include <vector>
#include <thread>
#include <condition_variable>
#include <cstdio>
#include <chrono>
using namespace std;

mutex mtx;
condition_variable cv;
int num_to_print = 0;

// 全局变量 num_to_print，表示当前应该打印的数字
// c % 3 == num_to_print 时我才打印，打印后 num_to_print 加一，以便让其他线程打印
void func(int c) {
    unique_lock<mutex> ulock(mtx);
    cv.wait(ulock, [c](){ return c % 3 == num_to_print; });
    // wait() 返回后，mtx 是 locked 状态，用来保护对 num_to_print 的写
    printf("%d %d\n", c % 3, c);
    num_to_print = (num_to_print + 1) % 3;

    // 下一句 mutex unlock，以便让其他线程拿到 lock，并继续执行 cv.wait() 使线程进入 wait 状态。
    // 否则，本函数退出时 mutex 才 unlock。若无此句，输出可明显看到，每个输出都等 1 秒，且完全按 c 的顺序输出。
    // 若有此句，可能有多个线程都进入 wait 状态。唤醒后，可有多个线程迅速按顺序输出。
    ulock.unlock();
    this_thread::sleep_for(chrono::milliseconds(1000));
    cv.notify_all(); // 通知所有线程，因为 num_to_print 已经改变
}

int main() {
    vector<thread> pool;
    for (int i = 0; i < 13; i++) {
        pool.push_back(thread(func, i));
    }
    for (auto& t : pool) {
        t.join();
    }
    return 0;
}
