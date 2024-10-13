import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

class FactorialRunnable implements Runnable {
    private int num;
    FactorialRunnable(int n) {
        this.num = n;
    }
    @Override
    public void run() {
        int fact = 1;
        for (int i = 1; i <= num; i++) {
            fact *= i;
        }
        System.out.println(fact);
    }
}

class FactorialCallable implements Callable<Integer> {
    private int num;

    public FactorialCallable(int n) {
        this.num = n;
    }
    public Integer call() throws Exception {
        int fact = 1;
        for (int i = 1; i <= num; i++) {
            fact *= i;
        }
        return fact;
    }
}

class runnable_callable_demo {
    private static void test_runnable_thread() {
        new Thread(new FactorialRunnable(8)).start();
    }

    private static void test_runnable_anonymous_thread() {
        int num = 10;
        // 用 anonymous class 实现 Runnable
        Runnable r = new Runnable() {
            @Override
            public void run() {
                int fact = 1;
                for (int i = 1; i <= num; i++) {
                    fact *= i;
                }
                System.out.println(fact);
            }
        };
        new Thread(r).start();
    }

    private static void test_runnable_lambda_thread() {
        int num = 9;
        // 用 lambda 实现 Runnable
        Runnable r = () -> {
                int fact = 1;
                for (int i = 1; i <= num; i++) {
                    fact *= i;
                }
                System.out.println(fact);
        };
        new Thread(r).start();
    }

    private static void test_runnable_es() {
        ExecutorService es = Executors.newSingleThreadExecutor();
        es.submit(new FactorialRunnable(7)); // 返回类型为 Future<?>，但不需要
        es.shutdown();
    }

    private static void test_callable_thread() {
        FactorialCallable c = new FactorialCallable(6); // 也可以用 Callable<> 类型
        FutureTask<Integer> futureTask = new FutureTask<>(c);
        // 紧凑写法
        // FutureTask<Integer> futureTask = new FutureTask<>(new FactorialCallable(6));
        new Thread(futureTask).start();
        try {
            Integer result = futureTask.get();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private static void test_callable_anonymous_thread() {
        int num = 10;
        // 用 anonymous class 实现 Runnable
        Callable<Integer> c = new Callable<>() {
            @Override
            public Integer call() {
                int fact = 1;
                for (int i = 1; i <= num; i++) { fact *= i; }
                return fact;
            }
        };
        FutureTask<Integer> futureTask = new FutureTask<>(c);
        new Thread(futureTask).start();
        try {
            Integer result = futureTask.get();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void test_callable_lambda_thread() {
        int num = 6;
        Callable<Integer> c = () -> {
            int fact = 1;
            for (int i = 1; i <= num; i++) { fact *= i; }
            return fact;
        };
        FutureTask<Integer> futureTask = new FutureTask<>(c);
        new Thread(futureTask).start();
        try {
            Integer result = futureTask.get();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void test_callable_es() {
        ExecutorService es = Executors.newSingleThreadExecutor();
        FactorialCallable c = new FactorialCallable(5);
        Future<Integer> future = es.submit(c);
        try {
            Integer result = future.get();
            System.out.println(result);
        } catch (Exception e) {
            e.printStackTrace();
        }
        es.shutdown();
    }


    public static void main(String[] args) throws Exception {
        test_runnable_thread();
        test_runnable_anonymous_thread();
        test_runnable_lambda_thread();
        test_runnable_es();
        test_callable_thread();
        test_callable_anonymous_thread();
        test_callable_lambda_thread();
        test_callable_es();
    }
}