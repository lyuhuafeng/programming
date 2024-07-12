import java.util.concurrent.CompletableFuture;

public class CompletableFutureTest {
    public static long factorial(int n) {
        long res = 1;
        for (int i = 1; i <= n; i++) {
            res *= i;
        }
        return res;
    }
    public static void do_test() {
        int num = 12;
        CompletableFuture<Long> cf = CompletableFuture.supplyAsync(() -> factorial(num));
        // CompletableFuture<Long> cf = CompletableFuture.supplyAsync(() -> { return factorial(num); } ); // 也可以
        while (!cf.isDone()) {
            System.out.println("CompletableFuture not finished yet...");
        }
        try {
            long result = cf.get();
            System.out.printf("result: %d%n", result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        do_test();
    }
}

