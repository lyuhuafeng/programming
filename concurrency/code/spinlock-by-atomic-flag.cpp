#include <atomic>
#include <thread>

// 用 atomic_flag 来实现 spinlock mutex
// flag == true,  mutex 是 locked
// flag == false, mutex 是 unlocked

class spinlock_mutex {
private:
    std::atomic_flag flag; // 初始，flag 设为 clear/false，表示 mutex 是 unlocked

public:
    spinlock_mutex() {}

    // warning: braces around scalar initializer [-Wbraced-scalar-init]
    // spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}

    // lock: busy-wait 直到 test_and_set() 返回 false，也就是等到 flag 被设为 true
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }
    // unlock: 简单 clear，flag 被设为 false
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

spinlock_mutex spin;

void work_on_resource() {
    spin.lock();
    spin.unlock();
}

int main() {
    std::thread t1(work_on_resource);
    std::thread t2(work_on_resource);
    t1.join();
    t2.join();
    return 0;
}