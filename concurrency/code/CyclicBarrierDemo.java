import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class CyclicBarrierDemo {

    private CyclicBarrier cyclicBarrier;
    private List<List<Integer>> partialResults = Collections.synchronizedList(new ArrayList<>());
    private Random random = new Random();
    private int NUM_ADDS;
    private int NUM_WORKERS;

    private void runSimulation(int numWorkers, int numAdds) {
        NUM_ADDS = numAdds;
        NUM_WORKERS = numWorkers;

        cyclicBarrier = new CyclicBarrier(NUM_WORKERS, new AggregatorThread()); // 1. 生成 barrier 对象
        System.out.println("spawning " + NUM_WORKERS + " worker threads to compute " + NUM_ADDS + " partial results each");
        for (int i = 0; i < NUM_WORKERS; i++) {
            Thread worker = new Thread(new NumberCruncherThread()); // 2. 生成多个工作线程并分别开始工作
            worker.setName("thread #" + i);
            worker.start();
        }
    }

    class NumberCruncherThread implements Runnable {

        @Override
        // 产生 NUM_ADDS 个数，放入 myResult 中。myResult 又放入 partialResults 中。
        public void run() {
            String myName = Thread.currentThread().getName();
            List<Integer> partialResult = new ArrayList<>();
            for (int i = 0; i < NUM_ADDS; i++) {
                Integer num = random.nextInt(10);
                System.out.println(myName + " crunching some numbers. final result: " + num);
                partialResult.add(num);
            }
            partialResults.add(partialResult);
            try {
                System.out.println(myName + " waiting for others to reach barrier.");
                cyclicBarrier.await(); // 3. 等待其他线程一起达到 barrier point
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }

    class AggregatorThread implements Runnable {

        @Override
        public void run() {
            String myName = Thread.currentThread().getName();
            System.out.println(myName + ": computing final sum of " + NUM_WORKERS + " workers, having " + NUM_ADDS + " numbers each.");
            int sum = 0;
            for (List<Integer> threadResult : partialResults) {
                System.out.print("adding ");
                for (Integer partialResult : threadResult) {
                    System.out.print(partialResult + " ");
                    sum += partialResult;
                }
                System.out.println();
            }
            System.out.println(Thread.currentThread().getName() + ": final result: " + sum);
        }

    }

    public static void main(String[] args) {
        new CyclicBarrierDemo().runSimulation(5, 3);
    }

}
