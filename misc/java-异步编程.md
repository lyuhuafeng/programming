
创建 thread 的两种方式：

继承 Thread 类，override 其 run() 方法。
创建该类实例，并调用其 start() 方法。

实现 Runnable 接口，实现其 run() 方法。
用该类的对象生成一个 Thread 类对象（作为 Thread 的构造函数的参数），并调用该 Thread 对象的 start() 方法。

```java
    public interface Runnable {
        public void run();
    }

    public class EventLoggingTask implements Runnable {
        private Logger logger = LoggerFactory.getLogger(EventLoggingTask.class);

        @Override
        public void run() {
            logger.info("Message");
        }
    }

    executorService = Executors.newSingleThreadExecutor();
    Future future = executorService.submit(new EventLoggingTask());
    executorService.shutdown();
```

共同缺陷：执行完任务后，无法获取结果

解法：通过 Callable 和 Future (since Java 5), 可在任务执行完后，得到结果。

callable，可以认为是增强版的 runnable。表示一个待执行的 task。
泛型接口。只有一个 call() 方法，返回类型就是泛型 V。
定义一个 task 类，继承自 callable，重写其 call() 方法。
用 executor service 提交该 task，返回 Future<V> 对象。

```java
    public interface Callable<V> {
        V call() throws Exception;
    }

    public class FactorialTask implements Callable<Integer> {
        int number;

        // standard constructors

        public Integer call() throws InvalidParamaterException {
            int fact = 1;
            for (int i = 1; i <= number; i++) {
                fact *= i;
            }
            return fact;
        }
    }

    FactorialTask task = new FactorialTask(5);
    Future<Integer> future = executorService.submit(task);
    int f = future.get().intValue();
```

Futrue是个接口。Future就是对于具体的Runnable或者Callable任务的执行结果进行取消、查询是否完成、获取结果。必要时可以通过get方法获取执行结果，该方法会阻塞直到任务返回结果。
cancel(), isCancelled(), isDone(), get(), get()

Runnable   Future
   |         |
  RunnableFuture
        |
    FutureTask

FutureTask 既可以作为 Runnable 被线程执行，又可以作为 Future 得到 Callable 的返回值。

```java
    public class SquareCalculator {    
        private ExecutorService executor = Executors.newSingleThreadExecutor();
        
        public Future<Integer> calculate(Integer input) {        
            return executor.submit(() -> {
                Thread.sleep(1000);
                return input * input;
            });
        }
    }
```

实际做计算的 call()，用 lambda 实现。

ForkJoinTask

to add later

CompletableFuture (since Java 8)
	implements Future, CompletionStage
to add later

ListenableFuture (by Google Guava)
	extends Future

Future: 获取结果还是不太不方便，只能以阻塞(get())或轮询(isDone())方式
ListenableFuture: 结果结算完成后实时通知到监听任务
相比FutureTask，本质上只是增加了任务的回调函数

https://www.fordawn.com/post/2020/listenablefurure-%E7%9A%84%E4%B8%80%E8%88%AC%E4%BD%BF%E7%94%A8/




Optional 的  orElse() vs. orElseGet()
orElse() 不管 optional 是否为空，都会执行。（不为空时，返回值不会使用）
orElseGet() 只在 optional 为空时执行

vela框架中，用了 ListenableFuture, 但取结果仍然用了 future.get(timeout, unit) 而不是 listener 方式。
它包装了 exception handling。
我要不要自己试试，直接用 get 而不用他包装了的 catchingOptional(get) 方式，看看 exception？

4个时间段并发，get() 后 set。
或，用 listener，自动set 数组相应的值。
如何处理超时？
initial idea: 包一个函数，这个函数的返回值为 future. future.get(timeout).

