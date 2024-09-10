#include <thread>
#include <future>

void func(std::promise<int> && p) {
    p.set_value(17);
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(func, std::move(p)); // 必须用 move()
    t.join();
    int i = f.get();
    printf("result: %d\n", i);
    return 0;
}