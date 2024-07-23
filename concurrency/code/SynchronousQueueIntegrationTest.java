import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class SynchronousQueueIntegrationTest {

    public static void test_latch() throws InterruptedException {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        AtomicInteger sharedState = new AtomicInteger();
        CountDownLatch countDownLatch = new CountDownLatch(1);

        Runnable producer = () -> {
            Integer producedElement = ThreadLocalRandom.current().nextInt();
            System.out.println("latch put:  " + producedElement);
            sharedState.set(producedElement);
            countDownLatch.countDown();
        };

        Runnable consumer = () -> {
            try {
                countDownLatch.await();
                Integer consumedElement = sharedState.get();
                System.out.println("latch take: " + consumedElement);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        };

        executor.execute(producer);
        executor.execute(consumer);
        executor.awaitTermination(500, TimeUnit.MILLISECONDS);
        executor.shutdown();
    }

    // @Test
    public static void test_sync_queue() throws InterruptedException {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        final SynchronousQueue<Integer> queue = new SynchronousQueue<>();

        Runnable producer = () -> {
            Integer producedElement = ThreadLocalRandom.current().nextInt();
            try {
                System.out.println("put:  " + producedElement);
                queue.put(producedElement);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        };

        Runnable consumer = () -> {
            try {
                Integer consumedElement = queue.take();
                System.out.println("take: " + consumedElement);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        };

        executor.execute(producer);
        executor.execute(consumer);
        executor.awaitTermination(500, TimeUnit.MILLISECONDS);
        executor.shutdown();
    }

    public static void main(String[] args) {
        try {
            test_sync_queue();
            test_latch();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}