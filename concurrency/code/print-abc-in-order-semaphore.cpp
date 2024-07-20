#include <vector>
#include <thread>
#include <semaphore>
#include <cstdio>
using namespace std;

// 三个 semaphore，每个完事后，释放下一个 semaphore。注意 sem[0] 初始化为 1，使得它启动时不用等其他 release
binary_semaphore sem[] = { binary_semaphore(1), binary_semaphore(0), binary_semaphore(0) };
int cnt = 0;

void func(int c) {
    while (true) {
        sem[c].acquire();
        printf("%c ", c + 'A');
        fflush(stdout);
        // 不能在这里 break！
        // 否则，本线程退出了，但其他线程还在等，就 block 住了。
        sem[(c + 1) % 3].release();
        // 得在 release 之后 break！
        if (++cnt == 10) {
            break;
        }
    }
}

int main() {
    vector<thread> pool;
    for (int i = 0; i < 3; i++) {
        // jthread t(func, i); // not available on my macos
        pool.push_back(thread(func, i));
    }
    for (auto& t : pool) {
        t.join();
    }
    return 0;
}
