import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Foo {
    private Lock lock = new ReentrantLock(); // 全局 lock/mutex
    private Condition cv1 = lock.newCondition(); // 全局 cv。注意是调用 lock/mutex 的方法生成的，与 c++ 不同
    private Condition cv2 = lock.newCondition();
    private boolean oneDone; // condition 条件
    private boolean twoDone;
    
    public Foo() {
        oneDone = false;
        twoDone = false;
    }

    public void first(Runnable printFirst) throws InterruptedException {
        lock.lock();
        try {
            printFirst.run();
            oneDone = true;
            cv1.signal(); // 通知其他线程。只通知一个。ac 了，但逻辑上感觉应该用 signalAll()?
        } finally {
            lock.unlock();
        }
    }

    public void second(Runnable printSecond) throws InterruptedException {
        lock.lock(); // 与 c++ 类似，先上锁
        // 没有 c++ raii 风格的 lock_guard/unique_lock，只能用 try，把「解锁」放在 finally 中
        try {
            while (!oneDone) {
                cv1.await(); // throws InterruptedException
            } // 没有 c++ 风格的「既等待又判断二合一」的 wait()，只能用 while 循环
            // 从 wait 返回后，自动重新上锁，lock 状态变为「locked」
            printSecond.run(); // 干活
            twoDone = true; // 修改条件，以便等会让其他线程醒后检查能通过
            //// 这里是否应该 lock.unlock() ？
            cv2.signal(); // 通知其他线程。只通知一个。ac 了，但逻辑上感觉应该用 signalAll()?
        } finally {
            lock.unlock();
        }
    }

    public void third(Runnable printThird) throws InterruptedException {
        lock.lock();
        try {
            while (!twoDone) {
                cv2.await();
            }
            printThird.run();
        } finally {
            lock.unlock();
        }
    }
}
