import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;
import java.util.Queue;
import java.util.LinkedList;
import java.lang.String;

class TaskQueue {
    private final Lock mtx = new ReentrantLock(); // 全局 lock/mutex
    private final Condition cv = mtx.newCondition(); // 全局 cv。由 lock/mutex 对象的方法创建，与 c++ 不同
    private Queue<String> queue = new LinkedList<>(); // 被保护的共享数据

    // 生产者
    public void addTask(String s) {
        mtx.lock(); // 写共享数据之前，先上锁。没有 c++ raii 风格的 wrapper，只能放在 try-finally 中
        try {
            queue.add(s); // 干活，写共享数据
            // 是否应该 mtx.unlock()?
            cv.signalAll(); // 通知消费者
        } finally {
            mtx.unlock(); // 释放锁
        }
    }

    public String getTask() throws InterruptedException {
        mtx.lock(); // 写共享数据前，先上锁
        try {
            while (queue.isEmpty()) {
                cv.await(); // throws InterruptedException
            } // 没有 c++ 风格的「既等待又判断二合一」的 wait()，只能用 while 循环
            // 从 wait 返回后，自动重新上锁，lock/mutex 状态变为「locked」
            return queue.remove(); // 干活，写共享数据
        } finally {
            mtx.unlock();
        }
    }
}