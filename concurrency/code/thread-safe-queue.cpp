#include <queue>
#include <mutex>
#include <condition_variable>

// 与 stack 很像，除了 (1)(2)(3) 处，push() 里 cv.notify_one()，两种 pop() 里的 cv.wait()。
// 吕问：为何不 notify_all()? 多个线程等着变为非 empty 的情况？因为唤醒多个也只能有一个 pop 成功，其余的还是会回去 sleep。
// 问题：若 wait_and_pop() 抛异常（数据倒也不会丢失，因异常只能出现在 pop() 之前 copy/move constructor 或 make_shared 分配内存），
// 则该线程 pop 未能成功，其他线程也没被唤醒，也没机会去 pop。
// 解法 1：改为 notify_all。缺点：大部分都白醒一场，然后继续回去睡。
// 解法 2：wait_and_pop() 里若抛异常，则调用 notify_one()
// 解法 3：queue 里不存数据，而是存数据的指针 shared_ptr。最佳。
//        只有指针赋值操作，不用分配内存，也没有 copy/move constructor，彻底消除异常风险。


template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mtx;
    std::queue<T> data_queue;
    std::condition_variable cv;

public:
    threadsafe_queue() {}

    void push(T new_value) {
        std::lock_guard<std::mutex> guard(mtx);
        data_queue.push(std::move(new_value));
        // 吕问：为何不先释放 lock？为何不 notify_all()?
        // 吕答：好像区别不大。
        // producer 先释放 lock，则 consumer 先拿到 lock 然后进入 wait；随后 producer notify，consumer wait 结束。
        // producer 先 notify 再释放 lock，则 consumer 拿到 lock 后试图 wait 时「非 empty」已经满足，就不用真的 wait 了。
        cv.notify_one(); // (1)
    }

    void wait_and_pop(T& val) { // (2)
        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [this]{ return !data_queue.empty(); });
        val = std::move(data_queue.front());
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() { // (3)
        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [this]{ return !data_queue.empty(); }); // (4)
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }
    bool try_pop(T& val) {
        std::lock_guard<std::mutex> ulock(mtx);
        if (data_queue.empty()) {
            return false;
        }
        val = std::move(data_queue.front()); // copy/move constructor 可能抛异常，但没修改任何数据，所以安全
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> ulock(mtx);
        if (data_queue.empty()) {
            return std::shared_ptr<T>(); // (5)
        }
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        // 两种情况可能导致抛异常。但没修改任何数据，所以安全。
        //     (a) make_shared 需给新对象分配内存，若内存不够，可能抛异常。
        //     (b) 分配内存后，copy/move 可能抛异常。
        data_queue.pop();
        return res;
    }
    bool empty() const {
        std::lock_guard<std::mutex> ulock(mtx);
        return data_queue.empty();
    }
};

int main() {}