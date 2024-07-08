# 同步机制

intrinsic lock，又称为 monitor lock 或 monitor

英语学习：intrinsic: 内在的、固有的

每个 object 都有一个 intrinsic lock。

synchronization 的两个方面：
- enforcing exclusive access to an object's state
- establishing happens-before relationships that are essential to visibility

## 用 synchronized 关键字

- synchronized method
- synchronized statement：一段代码，显式

reentrant synchronization 可重入的：一个线程多次 acquire 同一个 lock。（不能 acquire 别的线程拥有的 lock）

## mutex

任何 object 都可用作 mutex。需要用 synchronized 关键字。

```java
    private Object mutex = new Object();

    public int getNextSequence() {
        synchronized (mutex) {
            return super.getNextSequence();
        }
    }
```

## reentrant lock

since java 1.5。比 synchronized 关键字更好。

```java
    private ReentrantLock mutex = new ReentrantLock();
    public int getNextSequence() {
        try {
            mutex.lock();
            return super.getNextSequence();
        } finally {
            mutex.unlock();
        }
    }
```

## semaphore

since java 1.5。可支持多个线程同时访问。特点：任何 thread 都可以 release；但通常希望最初上锁的 thread 才能 release。

```java
    private Semaphore mutex = new Semaphore(3);

    public int getNextSequence() {
        try {
            mutex.acquire();
            return super.getNextSequence();
        } catch (InterruptedException e) {
            // exception handling code
        } finally {
            mutex.release();
        }
    }
```

# 异步编程：概述

- by threads
- by Future
- by CompletableFuture
- by ListenableFuture (by Google Guava)

# by threads

创建 thread 的两种方式：

1. 继承 Thread 类，override 其 run() 方法。
  - 创建该类实例，并调用其 start() 方法。
2. 实现 Runnable 接口，实现其 run() 方法。
  - 用该类的对象生成一个 Thread 类对象（作为 Thread 的构造函数的参数），并调用该 Thread 对象的 start() 方法。

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

# by Future

callable，可以认为是增强版的 runnable。表示一个待执行的 task。

泛型接口。只有一个 call() 方法，返回类型就是泛型 V。

定义一个 task 类，继承自 callable，重写其 call() 方法。

用 executor service 提交该 task，返回 `Future<V>` 对象。

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

Futrue 是个接口。Future 就是对于具体的 Runnable 或者 Callable 任务的执行结果进行取消、查询是否完成、获取结果。必要时可以通过 get 方法获取执行结果，该方法会阻塞直到任务返回结果。

cancel(), isCancelled(), isDone(), get(), get()

```
Runnable   Future
   |         |
  RunnableFuture
        |
    FutureTask
```

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

# by CompletableFuture

```
    CompletableFuture (since Java 8)
	    implements Future, CompletionStage
```

简单用法

```java
    CompletableFuture<String> cf = CompletableFuture.supplyAsync(() -> "Hello");
    // ...
    String result = cf.get(); // 其值为 "Hello"
```

异步计算阶乘，[完整代码](code/CompletableFutureTest.java)

```java
    int num = 12;
    CompletableFuture<Long> cf = CompletableFuture.supplyAsync(() -> factorial(num));
    while (!cf.isDone()) {
        System.out.println("CompletableFuture is not finished yet...");
    }
    long result = cf.get();
```
to add later

ref: https://www.baeldung.com/java-completablefuture

# by ListenableFuture (by Google Guava)

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

