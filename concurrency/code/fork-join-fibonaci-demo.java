import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinWorkerThread;
import java.util.concurrent.RecursiveTask;

// 2. 定义拆分任务，写好拆分逻辑 
class Fibonacci extends RecursiveTask<Integer> { 
    final int n; 
    Fibonacci(int n) { this.n = n; } 
 
    @Override 
    public Integer compute() { 
        System.out.println("thread: " + Thread.currentThread().getName()); 
        if (n <= 1) { return n; } // 递归结束
 
        Fibonacci f1 = new Fibonacci(n - 1); 
        f1.fork(); // 拆分成子任务 
        Fibonacci f2 = new Fibonacci(n - 2); 
        return f2.compute() + f1.join(); // f1.join 等待子任务执行结果 
    } 
}

class fork_join_fibonaci_demo {
    public static void main(String[] args) { 
        int n = 20; 
 
        // 为了追踪子线程名称，需要重写 ForkJoinWorkerThreadFactory 的方法 
        final ForkJoinPool.ForkJoinWorkerThreadFactory factory = pool -> { 
            final ForkJoinWorkerThread worker = ForkJoinPool.defaultForkJoinWorkerThreadFactory.newThread(pool); 
            worker.setName("my-thread " + worker.getPoolIndex()); 
            return worker; 
        }; 
 
        ForkJoinPool forkJoinPool = new ForkJoinPool(4, factory, null, false); // 创建分治任务线程池，可以追踪到线程名称 
        // ForkJoinPool forkJoinPool = new ForkJoinPool(4); // 快速创建 ForkJoinPool 方法 
 
        Fibonacci fibonacci = new Fibonacci(n); // 创建分治任务  
        Integer result = forkJoinPool.invoke(fibonacci); // 调用 invoke 方法启动分治任务 
        System.out.println("Fibonacci(" + n + ") result: " + result + "\n"); 
    } 
} 
 
