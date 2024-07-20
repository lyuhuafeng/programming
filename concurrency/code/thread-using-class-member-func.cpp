#include <thread>
#include <memory>
#include <cstdio>

class my_job {
private:
    std::shared_ptr<std::thread> mp_thread;

public:
    my_job() { }
    ~my_job() { }

    void thread_func(int arg1, int arg2) {
        printf("thread: %d, %d\n", arg1, arg2);
    }

    void start() {
        mp_thread.reset(new std::thread(&my_job::thread_func, this, 8888, 9999));
    }
    void stop() {
        if (mp_thread && mp_thread->joinable()) {
            mp_thread->join();
        }
    }

    void start2() {
        std::thread t(&my_job::thread_func, this, 1111, 2222);
        t.join();
    }

    void start3() {
        std::thread t(std::bind(&my_job::thread_func, this, 1111, 3333));
        t.join();
    }
};

int main() {
    my_job mythread;
    mythread.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mythread.stop();
    mythread.start2();
    mythread.start3();

    std::thread t(&my_job::thread_func, &mythread, 1234, 7890);
    t.join();
    std::thread t2(std::bind(&my_job::thread_func, &mythread, 1234, 5678));
    t2.join();
    return 0;
}

/*
std::bind() is for 'partial function application'.

若已有 callable f(a, b, c)，现需要一个新的只要两个参数的 callable 定义为 g(a, b) := f(a, 4, b)，

则 g 就是 f 的 'partial application'。可用 std::bind 实现：
    auto g = bind(f, _1, 4, _2);

用途：

1. 适配参数，用在 algorithm 算法中，例如：
    std::transform(vec.begin(), vec.end(), some_output, std::bind(std::pow, _1, 7));

2. 调整参数顺序，例如
    auto memcpy2 = bind(memcpy, _2, _1, _3);
    或 not2(bind(less<T>, _2, _1));
*/