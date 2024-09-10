import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/*
 * 打印 26 个字符，用 26 个线程。
 * 共用一个全局的 lock 和 condition.
 */

class PrintCharacterSequenceByCondition {
    private static final int COUNT = 26;
    private static volatile int currentIndex = 0; // currentIndex
    private static final ReentrantLock LOCK = new ReentrantLock();
    private static final Condition cv = LOCK.newCondition();
    // private static final List<Condition> conditionList = new ArrayList<>();

    public static void main(String[] args) {
        for (int i = 0; i < COUNT; i++) {
            // conditionList.add(LOCK.newCondition()); // Create a new condition for each thread.
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
            try {
                LOCK.lock();
                while (currentIndex != threadNumber) {
                    cv.await();
                }
                System.out.printf("%c %d%n", 'a' + currentIndex, threadNumber);
                currentIndex++;
                if (currentIndex >= COUNT) {
                    return;
                }
                cv.signalAll();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                LOCK.unlock();
            }
        }
    }
}
