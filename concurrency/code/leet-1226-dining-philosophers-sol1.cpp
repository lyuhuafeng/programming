// leet 1226 https://leetcode.cn/problems/the-dining-philosophers

#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

// 限制同时吃的人数，最多同时有 4 个人吃

class DiningPhilosophers {
private:
    mutex fork_mtx[5]; // 五个叉子

    mutex mtx;
    condition_variable cv;
    int eating_count; // 当前有多少人正在吃

public:
    DiningPhilosophers() : eating_count(0) {}

    void wantsToEat(int pid,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) 
    {
        unique_lock<mutex> ulock(mtx);
        cv.wait(ulock, [this]()->bool{ return eating_count < 4; }); // 当前吃者少于 4，我可以拿叉子
        eating_count++;
        {
            scoped_lock(fork_mtx[pid], fork_mtx[(pid + 1) % 5]);
            pickLeftFork();
            pickRightFork();
            eat();
            putLeftFork();
            putRightFork();
        }
        eating_count--;
        ulock.unlock();
        cv.notify_all(); // 吃完，通知其他人来吃
    }
};
