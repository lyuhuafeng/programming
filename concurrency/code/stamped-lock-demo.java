// import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.StampedLock;

class Point {
    private final StampedLock stampedLock = new StampedLock();

    private double x;
    private double y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void move(double deltaX, double deltaY) {
        long stamp = stampedLock.writeLock(); // 获取写锁
        try {
            x += deltaX;
            y += deltaY;
        } finally {
            stampedLock.unlockWrite(stamp); // 释放写锁
        }
    }

    public double distanceFromOrigin() {
        long stamp = stampedLock.tryOptimisticRead(); // 获得一个乐观读锁
        // 注意下面两行不是原子操作，两句之间可能 x, y 被写入，导致读到的数据不一致
        double currX = x;
        double currY = y;
        if (!stampedLock.validate(stamp)) { // 检查乐观读锁后是否有其他写锁发生
            stamp = stampedLock.readLock(); // 获取一个悲观读锁
            try {
                currX = x;
                currY = y;
            } finally {
                stampedLock.unlockRead(stamp); // 释放悲观读锁
            }
        }
        return Math.sqrt(currX * currX + currY * currY);
    }
}

class stamped_lock_demo {
    public static void main(String[] args) {
        Point p = new Point(100, 200);
        p.move(10, 20);
        double dist = p.distanceFromOrigin();
        System.out.println("distance from origin: " + dist);
    }
}