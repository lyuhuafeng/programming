#include <vector>
#include <thread>
#include <semaphore>
#include <cstdio>
using namespace std;

// 三个 semaphore，每个完事后，释放下一个 semaphore。注意 sem[0] 初始化为 1，使得它启动时不用等其他 release
binary_semaphore sem[] = { binary_semaphore(1), binary_semaphore(0), binary_semaphore(0) };

void func(int c) {
    sem[c % 3].acquire();
    printf("%c %d\n", 'A' + (c % 3), c);
    fflush(stdout);
    sem[(c + 1) % 3].release();
}

int main() {
    vector<thread> pool;
    for (int i = 0; i < 15; i++) {
        // jthread t(func, i); // not available on my macos
        pool.push_back(thread(func, i));
    }
    for (auto& t : pool) {
        t.join();
    }
    return 0;
}
