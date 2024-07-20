#include <exception>
#include <future>
#include <thread>
#include <utility>
#include <vector>
#include <iostream>

std::mutex mtx;

struct Div {
    void operator()(std::promise<int>&& intPromise, int a, int b) {
        try{
            if (b == 0) {
                throw std::runtime_error("illegal division by zero");
            }
            intPromise.set_value(a / b);
        } catch (...) {
            intPromise.set_exception(std::current_exception());
        }
    }
};

struct Requestor {
    void operator()(std::shared_future<int> f) {
        std::lock_guard<std::mutex> guard(mtx); // lock std::cout
        std::cout << "thread_id(" << std::this_thread::get_id() << "): " ;
        try {
            std::cout << "20 / 10 = " << f.get() << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
};

int main() {
    std::promise<int> p; // promise
    std::shared_future<int> f = p.get_future(); // future (shared)

    // 在单独线程中，计算结果，并通过 promise 设置结果
    std::vector<std::thread> vt;
    Div div;
    vt.emplace_back(div, std::move(p), 20, 10); // promise 只能 move 构造

    // 多个 shared future 都去取结果
    Requestor req;
    for (int i = 0; i < 5; i++) {
        vt.emplace_back(req, f); // shared future 可以 copy 构造。（但 future 也只能 move 构造）
    }

    for (std::thread& t : vt) {
        t.join();
    }
    return 0;
}
