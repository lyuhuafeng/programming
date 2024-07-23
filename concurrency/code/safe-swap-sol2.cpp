#include <mutex>
using namespace std;

class some_big_object {};

void my_swap(some_big_object& lhs,some_big_object& rhs);

class T {
private:
    some_big_object some_detail;
    std::mutex mtx;
public:
    T(some_big_object const& sd): some_detail(sd) {}

    friend void swap(T& lhs, T& rhs) {
        if (&lhs == &rhs) {
            return;
        } // 确保两个对象不同，否则下面 lock() 将试图对一个 mtx 做两次 lock，后果 undefined

        std::unique_lock<std::mutex> ulock_a(lhs.mtx, std::defer_lock);
        std::unique_lock<std::mutex> ulock_b(rhs.mtx, std::defer_lock);
        std::lock(ulock_a, ulock_b);

        my_swap(lhs.some_detail, rhs.some_detail);
    }
};

/*
(1) std::lock() 内部对两个 mtx 上锁时，任何一个都可能抛出异常。
    此时，std::lock() 会继续扩散该异常。
    若一个 lock 成功、另一个失败抛异常，则成功的那个也会自动 unlock，确保 all-or-nothing。

(2) defer_lock 选项表示：构造 unique_lock 对象时，不给 mutex 上锁，mutex 始终处于 unlock 状态。
    稍后，用 std::lock() 给两个 unique_lock 对象一起上锁，其实是给他俩对应的两个 mutex 一起上锁。

*/

int main() {}
