import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/*
 * 打印 26 个字符，用 5 个线程。
 * 每个线程有个 condition，放在线程外面。id 对应一个字符；
 * 线程里 wait 到「全局 val == 自己 id」，就输出自己 id 对应的字符，然后 signal 下一线程。
 * 所有 condition 都是从同一个 lock 里创建的。
 */

class PrintCharacterSequenceByCondition {
    private static final int CHARACTER_COUNT = 26;
    private static final int THREAD_COUNT = 5; //concurrent threads numbers
    private static volatile int currentIndex = 0; //currentIndex
    private static final ReentrantLock LOCK = new ReentrantLock();
    private static final List<Condition> conditionList = new ArrayList<>();

    public static void main(String[] args) {
        for (int i = 0; i < THREAD_COUNT; i++) {
            conditionList.add(LOCK.newCondition()); //Create a new condition for each thread.
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
            while (true) {
                try {
                    LOCK.lock();
                    
                    if (currentIndex % CHARACTER_COUNT != threadNumber) {
                        conditionList.get(threadNumber).await();
                    }
                    int nextIndex = (threadNumber + 1) % conditionList.size(); // id of next thread/condition

                    if (currentIndex == CHARACTER_COUNT) {
                        System.out.println("task completed, closing " + nextIndex);
                        conditionList.get(nextIndex).signal();
                        return;
                    }

                    System.out.printf("%c %d%n", 'a' + currentIndex, threadNumber);
                    currentIndex++;
                    conditionList.get(nextIndex).signal();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } finally {
                    LOCK.unlock();
                }
            }
        }
    }
}
