import java.util.concurrent.Executors;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

class SquareCalculator {
    private final ExecutorService executor = Executors.newFixedThreadPool(3);
    void shutdown() {
        executor.shutdown();
    }

    Future<Integer> calculate(Integer i) {
        return executor.submit(() -> {
            Thread.sleep(1000);
            return i * i;
        });
    }
}

class square_calc_callable_future_demo {
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        SquareCalculator squareCalculator = new SquareCalculator();

        Future<Integer> f1 = squareCalculator.calculate(10);
        Future<Integer> f2 = squareCalculator.calculate(100);

        while (!(f1.isDone() && f2.isDone())) {
            System.out.println(
                String.format("f1: %s, f2: %s", 
                    f1.isDone() ? "done" : "not done", 
                    f2.isDone() ? "done" : "not done"
                )
            );
            Thread.sleep(300);
        }

        Integer result1 = f1.get();
        Integer result2 = f2.get();
        System.out.println(result1 + " and " + result2);
        squareCalculator.shutdown();
    }
}
