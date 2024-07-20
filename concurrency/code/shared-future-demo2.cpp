#include <cstdio>
#include <future>
#include <thread>
#include <vector>

// 主线程：创建三个线程，每个线程都等待一个 shared future
// 每个线程：简单输出从 shared future 中取得的结果

void compute(int id, std::shared_future<int> f) {
    printf("thread #%d, got result: %d\n", id, f.get());
}

int main() {
    std::promise<int> p;
    std::shared_future<int> f = p.get_future().share();

    std::vector<std::thread> threads;

    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(compute, i, f);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    p.set_value(42);

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}