#include <mutex>
using namespace std;

class some_big_object;

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
        std::lock(lhs.mtx, rhs.mtx); // 1
        std::lock_guard<std::mutex> guard_a(lhs.mtx, std::adopt_lock);
        std::lock_guard<std::mutex> guard_b(rhs.mtx, std::adopt_lock); // 2

        // std::scoped_lock guard(lhs.mtx, rhs.mtx); // since c++17, 上三句也可用这一句代替。 // 3
        my_swap(lhs.some_detail, rhs.some_detail);
    }
};

/*
(1) std::lock() 内部对两个 mtx 上锁时，任何一个都可能抛出异常。
    此时，std::lock() 会继续扩散该异常。
    若一个 lock 成功、另一个失败抛异常，则成功的那个也会自动 unlock，确保 all-or-nothing。

(2) adopt_lock 选项表示：(adopt: 收养)
    mtx 已经 lock 了，guard 应该 adopt the ownership of the existing lock on the mutex
    而不是 lock the mutex in the constructor

(3) c++17 提供了 scoped_lock，与 lock_guard<> 完全一样，但可以接受多个 mutex 作为参数。
    这一句可取代上面三句

*/

int main() {}
