import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.time.Instant;

/*
 * 打印 26 个字符，用 26 个线程。
 * 共用一个全局的 lock 和 condition.
 *
 * 整个过程大致如下：
 * 刚开始，大家都去拿 lock。只有一个拿到。但它不满足打印条件，于是调用 cv.await() 进入 wait 状态并释放 lock。
 * 于是其他线程中的某一个拿到 lock…… 以此类推，很多线程进入了 wait 状态。
 * 直到某个线程拿到 lock 并满足打印条件，于是干活（sleep 1s）并打印。然后调用 cv.signalAll() 唤醒所有线程。
 * 其他线程被唤醒，要从 cv.await() 返回并需要拿到 lock。
 * 注意，cv.signalAll() 时，lock 还没释放，所以 cv.await() 要一直等到 finally 里的 LOCK.unlock() 执行后，才可能拿到锁，才能返回。
 * 为验证这一点，特意在 cv.signalAll() 之后又 sleep 2s。从 log 看，确实是 LOCK.unlock() 后，其他某个线程的 cv.await() 才返回。
 * 
 * 我感觉，应该在 signalAll() 之前就释放 lock。（看 c++ 定式里，也确实是 release lock 后才调用 notifyAll()）。
 * 但 java 里把 lock 释放放在了 finally 里，就没法在 signalAll() 之前再调用 signalAll() 了，否则会调用两次 signalAll()。
 * c++ raii 方式是可以的。
 */

class PrintAbcByCondition {
    private static final int COUNT = 15;
    private static volatile int currentIndex = 0; // currentIndex
    private static final ReentrantLock LOCK = new ReentrantLock();
    private static final Condition cv = LOCK.newCondition();

    public static void main(String[] args) {
        for (int i = 0; i < COUNT; i++) {
            new Thread(new PrintThread(i)).start();
        }
    }

    static class PrintThread implements Runnable {
        private final int threadNumber;

        public PrintThread(int threadNumber) {
            this.threadNumber = threadNumber;
        }

        @Override
        public void run() {
            System.out.println(Instant.now() + " " + threadNumber + " started"); System.out.flush();
            try {
                System.out.println(Instant.now() + " " + threadNumber + " before lock"); System.out.flush();
                LOCK.lock();
                System.out.println(Instant.now() + " " + threadNumber + " locked"); System.out.flush();
                while (currentIndex != threadNumber % 3) {
                    System.out.println(Instant.now() + " " + threadNumber + " waiting"); System.out.flush();
                    cv.await();
                    System.out.println(Instant.now() + " " + threadNumber + " woke up"); System.out.flush();
                }
                /* do work */ Thread.sleep(1000);
                System.out.println(Instant.now() + " " + (char) ('a' + currentIndex) + " " + threadNumber); System.out.flush();
                currentIndex = (currentIndex + 1) % 3;
                System.out.println(Instant.now() + " " + threadNumber + " before signal all"); System.out.flush();
                LOCK.unlock();
                cv.signalAll();
                System.out.println(Instant.now() + " " + threadNumber + " signaled all"); System.out.flush();
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                System.out.println(Instant.now() + " " + threadNumber + " before unlock"); System.out.flush();
                LOCK.unlock();
                System.out.println(Instant.now() + " " + threadNumber + " after unlock"); System.out.flush();
            }
        }
    }
}
