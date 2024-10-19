import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

/*
 * 打印 26 个字符，用 5 个线程。
 * 每个线程有个 condition，放在线程外面。id 对应一个字符；
 * 线程里 wait 到「全局 val == 自己 id」，就输出自己 id 对应的字符，然后 signal 下一线程。
 * 所有 condition 都是从同一个 lock 里创建的。
 */

class PrintCharacterSequenceByCondition {
    private static final int COUNT = 26;
    private static volatile int currentIndex = 0; // currentIndex
    private static final ReentrantLock LOCK = new ReentrantLock();
    private static final List<Condition> conditionList = new ArrayList<>();

    public static void main(String[] args) {
        ExecutorService es = Executors.newSingleThreadExecutor();
        for (int i = 0; i < COUNT; i++) {
            conditionList.add(LOCK.newCondition()); // Create a new condition for each thread.
            es.submit(new PrintThread(i)); // 不需要其返回值
        }
        es.shutdown();
    }

    static class PrintThread implements Callable<Integer> {
        private final int threadNumber;

        public PrintThread(int threadNumber) {
            this.threadNumber = threadNumber;
        }

        // @Override
        public Integer call() {
            try {
                LOCK.lock();
                while (currentIndex != threadNumber) {
                    conditionList.get(threadNumber).await();
                }
                System.out.printf("%c %d%n", 'a' + currentIndex, threadNumber);
                currentIndex++;
                if (currentIndex >= COUNT) {
                    return 1; //threadNumber;
                }
                conditionList.get(currentIndex).signal();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                LOCK.unlock();
            }
            return 1;
        }
    }
}