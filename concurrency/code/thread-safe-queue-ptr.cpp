#include <queue>
#include <mutex>
#include <condition_variable>

// 改进版本：queue 里存 shared_ptr 而不是直接存数据值

template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mtx;
    std::queue<std::shared_ptr<T>> data_queue; // queue 里存指针而不是直接存值
    std::condition_variable cv;

public:
    threadsafe_queue() {}

    void push(T new_value) {
        std::shared_ptr<T> new_value_ptr = std::make_shared<T>(std::move(new_value)); // 不同之处
        // 额外好处：给新元素分配内存，昂贵操作，放在 lock 之外，提高性能
        std::lock_guard<std::mutex> guard(mtx);
        data_queue.push(new_value_ptr); // 不同之处
        cv.notify_one(); // (1)
    }

    void wait_and_pop(T& val) { // (2)
        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [this]{ return !data_queue.empty(); });
        val = std::move(*data_queue.front()); // 不同之处：*
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() { // (3)
        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [this]{ return !data_queue.empty(); }); // (4)
        std::shared_ptr<T> res = data_queue.front(); // 不同之处：指针，直接赋值
        data_queue.pop();
        return res;
    }
    bool try_pop(T& val) {
        std::lock_guard<std::mutex> ulock(mtx);
        if (data_queue.empty()) {
            return false;
        }
        val = std::move(*data_queue.front()); // 不同之处：*
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> ulock(mtx);
        if (data_queue.empty()) {
            return std::shared_ptr<T>(); // (5)
        }
        std::shared_ptr<T> res = data_queue.front(); // 不同之处：指针，直接赋值
        data_queue.pop();
        return res;
    }
    bool empty() const {
        std::lock_guard<std::mutex> ulock(mtx);
        return data_queue.empty();
    }
};

int main() {}