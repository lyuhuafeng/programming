import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.Lock;

class Counter {
    private final ReadWriteLock rwlock = new ReentrantReadWriteLock();
    private final Lock rlock = rwlock.readLock();
    private final Lock wlock = rwlock.writeLock();
    private int[] counts = new int[10];

    public void inc(int index) {
        wlock.lock(); // 加写锁
        try {
            counts[index] += 1;
        } finally {
            wlock.unlock(); // 释放写锁
        }
    }

    public int get(int index) {
        rlock.lock(); // 加读锁
        try {
            return counts[index];
        } finally {
            rlock.unlock(); // 释放读锁
        }
    }
}