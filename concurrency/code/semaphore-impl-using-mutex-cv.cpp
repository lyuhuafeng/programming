#include <mutex>
#include <condition_variable>

// 没有规定 max_value 值。n 是初始值，不是 max_value。
// 不过 c++ semaphore 也不阻止 sem 超过 max_value，只是超过之后的行为是 undefined。

class my_semaphore {
private:
    int n;
    std::mutex mtx;
    std::condition_variable cv;

public:
    my_semaphore(int n_): n{n_} {}

public:
    void acquire() {
        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [this]{ return n > 0; });
        n--;
    }

    void release() {
        {
            std::lock_guard<std::mutex> guard(mtx);
            n++; // 不管是否超过
        }
        cv.notify_all();
    }
};

// class H2O {
// private:
//     my_semaphore s_hIn, s_oIn;
//     my_semaphore s_hBarrier, s_oBarrier;

// public:
//     H2O(): s_hIn{2}, s_oIn{1}, s_hBarrier{0}, s_oBarrier{0} {}

//     void hydrogen(function<void()> releaseHydrogen) {
//         s_hIn.acquire();
//         s_oBarrier.signal();
//         s_hBarrier.acquire();
//         releaseHydrogen();
//         s_hIn.signal();
//     }

//     void oxygen(function<void()> releaseOxygen) {
//         s_oIn.acquire();
//         s_oBarrier.acquire();
//         s_oBarrier.acquire();
//         s_hBarrier.signal();
//         s_hBarrier.signal();
//         releaseOxygen();
//         s_oIn.signal();
//     }
// };

