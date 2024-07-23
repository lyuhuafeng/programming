#include <iostream>
#include <mutex>
#include <latch>
#include <thread>
#include <string>

// worker latch 初值为 worker_cnt。每个 worker 线程里，完成工作后，调用 worker_latch.count_down() 通知 boss 线程。
// boss 线程中启动所有 worker 线程后，调用 worker_latch.wait() 等待所有 worker 线程完成工作。

// gohome latch 初值为 1。boss 线程里，在合适的时机，调用 gohome_latch.count_down() 通知所有 worker 线程。
// 每个 worker 线程中，完成工作后，就调用 gohome_latch.wait() 等待 boss 线程通知。

// 若用 cv 代替：worker 



// std::latch workDone(6);
// std::latch goHome(1);
std::mutex coutMutex;

int work_done = 0;
bool go_home = false;
std::mutex work_done_mtx, go_home_mtx;
std::condition_variable work_done_cv, go_home_cv;

void synchronizedOut(const std::string s) {
    std::lock_guard<std::mutex> guard(coutMutex); 
    std::cout << s;
}

class Worker {
private:
    std::string name;
public:
    Worker(std::string n): name(n) {}

    void operator() () {
        // notify the boss when work is done 
        synchronizedOut("    " + name + ": " + "Work done!\n");

        // workDone.count_down();
        {
            std::lock_guard<std::mutex> guard(work_done_mtx);
            work_done++;
        }
        work_done_cv.notify_one();

        // waiting before going home
        // goHome.wait();
        std::unique_lock<std::mutex> ulock(go_home_mtx);
        go_home_cv.wait(ulock, []{ return go_home; });
        ulock.unlock();
        synchronizedOut("    " + name + ": " + "Good bye!\n");
    }
};

int main() {
    std::cout << "BOSS: START WORKING! " << '\n';
    std::vector<std::thread> workers;
    for (const std::string &s : {"Herb", "Scott", "Bjarne", "Andrei", "Andrew", "David"}) {
        workers.emplace_back(Worker(s));
    }

    // workDone.wait();
    std::unique_lock<std::mutex> ulock(work_done_mtx);
    work_done_cv.wait(ulock, []{ return work_done == 6;});
    ulock.unlock();

    std::cout << '\n';

    // goHome.count_down();
    {
        std::lock_guard<std::mutex> guard(go_home_mtx);
        go_home = true;
    }
    go_home_cv.notify_all();

    std::cout << "BOSS: GO HOME!" << '\n';

    for (std::thread &t : workers) {
        t.join();
    }
    return 0;
}
