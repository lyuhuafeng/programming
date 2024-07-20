// leet 1226 https://leetcode.cn/problems/the-dining-philosophers

#include <mutex>
#include <functional>
using namespace std;

// 当某一个哲学家能够同时拿起左右两只叉子时，才让他拿，这样就能够保证不会因为每个科学家都只拿了一只叉子而导致死锁。
// 为了保证能够同时拿起，我们需要对拿叉子这一步骤进行加锁，保证哲学家能够同时拿起一双叉子，而不会拿了一边后另一边被人抢走

class DiningPhilosophers {
private:
    mutex mtx;	
    mutex fork_mtx[5];

public:
    DiningPhilosophers() {}

    // ac, 2024.07.19
    void wantsToEat(int pid,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) 
    {
        // 对「拿叉子」加锁，保证其能同时拿起一双，而不会被其他人抢走
        mtx.lock();
        fork_mtx[pid].lock();
        fork_mtx[(pid + 1) % 5].lock();
        mtx.unlock();
		
        pickLeftFork();	
        pickRightFork();
        eat();	
        putLeftFork();
        putRightFork();
        
        // 解锁，让其他人获取叉子
        fork_mtx[pid].unlock();
        fork_mtx[(pid + 1) % 5].unlock();
    }

    // 这种方法就不能 ac，不知为何。
    // 可能是因为 scoped_lock 要同时拿两个，而上面 ac 代码是分别拿两个？
    // 但「限制最多 4 人同时吃」的代码，也是用的 scoped_lock？
    void wantsToEat_wrong(int pid, ...) {
        //对拿叉子进行这一流程进行加锁，保证其能同时拿起一双，而不会被其他人抢走
        mtx.lock();
        scoped_lock(fork_mtx[pid], fork_mtx[(pid + 1) % 5]);//.lock();
        mtx.unlock();

        // 拿叉子、吃、放叉子：此处省略 5 行

        // 两个 fork_mtx 应该自动销毁
    }
};

