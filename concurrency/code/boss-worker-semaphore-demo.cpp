#include <iostream>
#include <mutex>
#include <semaphore>
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

std::counting_semaphore<6> work_done_sem(0);
std::counting_semaphore<6> go_home_sem(0);

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
        work_done_sem.release();

        // waiting before going home
        // goHome.wait();
        go_home_sem.acquire();
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
    for (int i = 0; i < 6; ++i) { // 只有一个线程 acquire，所以不用 mutex 保护
        work_done_sem.acquire();
    }

    std::cout << '\n';

    // goHome.count_down();
    go_home_sem.release(6);

    std::cout << "BOSS: GO HOME!" << '\n';

    for (std::thread &t : workers) {
        t.join();
    }
    return 0;
}
