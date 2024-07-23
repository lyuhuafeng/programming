import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

class FactorialRunnable implements Runnable {
    private int number;
    FactorialRunnable(int number) {
        this.number = number;
    }
    @Override
    public void run() {
        int fact = 1;
        for (int i = 1; i <= number; i++) {
            fact *= i;
        }
        System.out.println("Factorial of " + number + ": " + fact);
    }

}

class FactorialTask implements Callable<Integer> {
    int number;

    public FactorialTask(int number) {
        this.number = number;
    }
    public Integer call() throws Exception {
        int fact = 1;
        for (int i = 1; i <= number; i++) {
            fact *= i;
        }
        return fact;
    }
}

public class runnable_callable_demo {
    private static void test_runnable_thread() {
        new Thread(new FactorialRunnable(8)).start();
    }
    private static void test_runnable_es() {
        ExecutorService es = Executors.newSingleThreadExecutor();
        Future future = es.submit(new FactorialRunnable(7));
        es.shutdown();
    }
    private static void test_runnable_anonymous() {
        int number = 10;
        // 用 anonymous class 实现 Runnable
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                int fact = 1;
                for (int i = 1; i <= number; i++) {
                    fact *= i;
                }
                System.out.println("Factorial of " + number + ": " + fact);
            }
        };
        new Thread(runnable).start();
    }

    private static void test_runnable_lambda() {
        int number = 9;
        // 用 lambda 实现 Runnable
        Runnable runnable = () -> {
                int fact = 1;
                for (int i = 1; i <= number; i++) {
                    fact *= i;
                }
                System.out.println("Factorial of " + number + ": " + fact);
        };
        new Thread(runnable).start();
    }

    private static void test_callable_thread() {
        FactorialTask task = new FactorialTask(6); // 也可以用 Callable<> 类型
        // 紧凑写法
        // FutureTask<Integer> futureTask = new FutureTask<>(new FactorialTask(6));
        FutureTask<Integer> futureTask = new FutureTask<>(task);
        new Thread(futureTask).start();
        try {
            Integer result = futureTask.get();
            System.out.println("Factorial of 6: " + result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void test_callable_es() {
        ExecutorService es = Executors.newSingleThreadExecutor();
        FactorialTask task = new FactorialTask(5);
        Future<Integer> future = es.submit(task);
        try {
            Integer result = future.get();
            System.out.println("Factorial of 5: " + result);
        } catch (Exception e) {
            e.printStackTrace();
        }
        es.shutdown();
    }


    public static void main(String[] args) throws Exception {
        test_runnable_thread();
        test_runnable_es();
        test_runnable_anonymous();
        test_runnable_lambda();
        test_callable_thread();
        test_callable_es();
    }
}