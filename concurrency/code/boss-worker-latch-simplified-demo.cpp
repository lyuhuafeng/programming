#include <iostream>
#include <mutex>
#include <latch>
#include <thread>
#include <string>

// worker latch 初值为 worker_cnt。每个 worker 线程里，完成工作后，调用 worker_latch.count_down() 通知 boss 线程。
// boss 线程中启动所有 worker 线程后，调用 worker_latch.wait() 等待所有 worker 线程完成工作。

// gohome latch 初值为 1。boss 线程里，在合适的时机，调用 gohome_latch.count_down() 通知所有 worker 线程。
// 每个 worker 线程中，完成工作后，就调用 gohome_latch.wait() 等待 boss 线程通知。




std::latch workDone(6);
// std::latch goHome(1);
std::mutex coutMutex;

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
        // // waiting before going home
        // goHome.wait();
        workDone.arrive_and_wait(); // 这一行等效于上面被注释掉的两行代码
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
    // std::cout << '\n';
    // goHome.count_down();
    // std::cout << "BOSS: GO HOME!" << '\n';
    ////// 上面的的 wait() 和 count_down() 都不需要了

    for (std::thread &t : workers) {
        t.join();
    }
    return 0;
}
