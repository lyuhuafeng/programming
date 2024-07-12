#include <vector>
#include <thread>
#include <condition_variable>
#include <cstdio>
using namespace std;

mutex mtx;
condition_variable cv;
int num = 0;

// 打印 ch 4 遍
// 全局变量 num
// ch == num 时我才打印，打印后 num 加一，以便让其他线程打印
void func(char ch) {
    int n = ch - 'A';
    for(int i = 0; i < 4; i++) {
        unique_lock<mutex> ulock(mtx);
        cv.wait(ulock, [n](){ return n == num; });
        // wait() 返回后，mtx 是 locked 状态，用来保护对 num 的写
        printf("%c ", ch);
        num = (num + 1) % 3;

        // 下一句不要也可以。是因为在 for scope 结束时自动销毁了？
        ulock.unlock(); // mtx unlock，以便让其他线程可以拿到锁，进入 cv.wait() 状态
        cv.notify_all();
    }
}

int main() {
    vector<thread> pool;
    for (char c = 'A'; c <= 'C'; c++) {
        pool.push_back(thread(func, c));
    }
    for (auto& t : pool) {
        t.join();
    }
    return 0;
}
