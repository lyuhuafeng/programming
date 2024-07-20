// leet 1226 https://leetcode.cn/problems/the-dining-philosophers

#include <mutex>
#include <functional>
using namespace std;

// 规定奇数位的哲学家先拿左边的叉子，再拿右边的叉子。而偶数位的哲学家先拿右边的再拿左边的，此时竞争情况如下图所示

// 1, p1, 2, p2, 3, p3, 4, p4, 5, p5, 1

// 每人拿叉子的顺序：
// p1: 1, 2
// p2: 3, 2
// p3: 3, 4
// p4: 5, 4
// p5: 5, 1

// 第一轮，p2、p3 争抢 3，p4、p5 争抢 5，只有 p1 没人跟他抢，顺利得到 1。
// 随后，

class DiningPhilosophers {
private:
    mutex fork_mtx[5];

public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) 
    {
        if (philosopher & 1) { //如果是奇数则先抢左后抢右
            fork_mtx[philosopher].lock();
            fork_mtx[(philosopher + 1) % 5].lock();
            pickLeftFork();
            pickRightFork();
        } else { //如果是偶数则先抢右后抢左
            fork_mtx[(philosopher + 1) % 5].lock();
            fork_mtx[philosopher].lock();
            pickRightFork();
            pickLeftFork();
        }
        eat();
        putLeftFork();
        putRightFork();

        fork_mtx[philosopher].unlock();
        fork_mtx[(philosopher + 1) % 5].unlock();
    }
};
