# 同步机制


java 中的 lock 可分成两类
- synchronization lock
- java.util.concurrent 包中的 lock
  - Lock interface, ReadWriteLock interface
  - LockSupport blocking primitive
  - Condition condition
  - Abstract{Ownable, Queued, QueuedLong}Synchronizer abstract classes
  - ReentrantLock exclusive lock, ReentrantReadWriteLock read-write lock

JUC lock 的不同语义：
- fair/unfair: 不同线程 acquire lock 的机制是否 fair
- reentrant：有些 lock 可被同一个线程 acquire 多次

AQS, AbstractQueuedSynchronizer 类：管理各种 lock 的抽象类。lock 的很多 public 方法是在这个类中定义的。是 exclusive lock 和 shared locks 的共同的父类。

- exclusive lock: lock 在某一时刻只能被一个 thread 持有。如 ReentrantLock 和 ReentrantReadWriteLock.writeLock。
  - 可分为 fair 和 unfair 两种
- shared lock: lock 在某一时刻可被多个 thread 持有，可共享。如 ReentrantReadWriteLock.readLock, CyclicBarrier, CountDownLatch and Semaphore 等。<font color=red>(吕：存疑，从概念上，后面这些不算 lock 吧？)</font>

CLH queue (Craig, Landin, and Hagersten lock queue): AQS 中的 waiting-for-lock thread queue
- 是个 non-blocking FIFO queue。意思是，当 insert/remove 一个元素，it will not block under concurrent conditions, but through spin lock and CAS to ensure the atomicity of node insertion and removal. <font color=red>没看太明白</font>

fair, unfair: 在 ReentrantLock 的构造函数中指定。缺省为 unfair（效率高）。
- fair: 每个想 acquire lock 的 thread 都会被放到 CLH queue 中，按照 FIFO 方式排队。
- unfair: 先试图直接拿 lock；若不成功，则放入 CLH queue，后面跟 fair 情况一样。

比较：
- unfair 效率高，fair 因大量线程切换而有性能损失。
- unfair 刚释放锁的线程再次获取同步状态的概率比较大，会出现连续获取锁的情况。fair 可减少「饥饿」发生的概率，等待越久的请求越是可以得到最先满足。

# synchronized 关键字，利用 object 的 intrinsic lock

java 1.5 之前，只能用 synchonized 关键字

每个 object 都有一个 intrinsic lock，又称为 monitor lock 或 monitor

英语学习：intrinsic: 内在的、固有的

synchronization 的两个方面：
- enforcing exclusive access to an object's state
- establishing happens-before relationships that are essential to visibility

两类：
- synchronized method 同步方法
- synchronized statement 同步代码块：一段代码，显式

多个线程同时执行「一块代码」或「一个函数」。

`synchronized (object)`，是用该 object 做 mutex。严谨说法：某线程 acquire 了与 object/mutex 关联的 intrinsic lock (monitor lock, monitor)。

任何 object 都可用作 mutex。但，既然用作 mutex，该 object 应该是 class 全局可见的、各 thread 都能访问到的。或者是自定义的类成员变量，或者直接用 this。

```java
    private Object mtx = new Object();

    public int getNextSequence() {
        synchronized (mtx) { // 用自定义的 class 成员变量做 mutex
            return super.getNextSequence();
        }
        // 或
        synchronized (this) { // 用 class object 做 mutex
            return super.getNextSequence();
        }
    }
```

synchronized method，相当于 `synchronized (this)`；

synchronized static method，相当于 `synchronized (class_name.class)`；

c++ 可用 function 来创建 thread；java 好像不行，得用 ... 来创建 thread。

reentrant synchronization 可重入的：一个线程多次 acquire 同一个 lock。（不能 acquire 别的线程拥有的 lock）

synchronized 的缺陷：
《Java高并发编程详解:多线程与架构设计》可供参考的内 容如下。
- 第4章“线程安全与数据同步”：何种情况之下会出现死锁以及如何诊断。
- 第5章“线程间通信”:其中的5.4节自定义显式锁BooleanLock为 读者分析了synchronized关键字的缺陷，以及如何实现一个显式 锁的方法。 
- 第17章“读写分离锁”:当前共 享资源在所有线程间进行读操作的情况之下无须加锁提高并发程 序性能，并且给出了解决方案以及程序实现。

# Lock 接口

一般意义上的 mutex，就是 Lock 接口的实例，通常也称为 lock。

# ReentrantLock

since java 1.5。比 synchronized 关键字更好。

为确保释放成功，要将 `unlock()` 放在 finally 中。

下面两个例子，`lock()` 分别放在了 try 里和 try 外。

```java
    private ReentrantLock mtx = new ReentrantLock();
    public int getNextSequence() {
        try {
            mtx.lock();
            return super.getNextSequence();
        } finally {
            mtx.unlock();
        }
    }

    private int x;
    private final Lock rlock = new ReentrantLock();
    public void lockInc() {
        rlock.lock();
        try {
            x++;
        } finally {
            rlock.unlock();
        }
    }
```

# ReadWriteLock 读写锁

适用于读多写少的场景。只允许一个线程写入；允许多个线程在没有写入时同时读取。

例，[代码](code/rw-counter-demo.java)
```java
    private final ReadWriteLock rwlock = new ReentrantReadWriteLock();
    private final Lock rlock = rwlock.readLock();
    private final Lock wlock = rwlock.writeLock();
```

# StampedLock：更高效的读写锁

是一种乐观锁。stamp（盖戳）意思就是 lock version。

三种模式：write, read, optimistic read.

读的过程中，允许其他线程获取写锁后写入。可能不一致，所以读完需查一下，读过程中是否有其他写锁发生；若有，用「悲观读锁」再读一遍。

不可重入，不是 re-entrant 的。

https://www.liaoxuefeng.com/wiki/1252599548343744/1309138673991714

https://medium.com/@aayushbhatnagar_10462/java-concurrency-through-stamped-locks-eb65e9a675c1

注意，StampedLock 的 writeLock()、tryOptimisticRead()、readLock() 三个方法，返回的结果并不是个 lock，而是一个 long 类型的「版本」，该「版本」用做各 unlock 方法的参数。以 write 为例：

```java
// 初以为的方式，错误！
    Lock wlock = stampedLock.writeLock(); // 获取写锁
    wlock.unlock(); // 释放写锁
// 实际的方式
    long stamp = stampedLock.writeLock(); // 获取写锁
    stampedLock.unlockWrite(stamp); // 释放写锁
```

实际代码示例：[stamped-lock-demo.java](code/stamped-lock-demo.java)

```java
    private final StampedLock stampedLock = new StampedLock();
    
    // 写，跟普通 ReadWriteLock 类似
    long stamp = stampedLock.writeLock(); // 获取写锁
    try { /* write data */ } finally { stampedLock.unlockWrite(stamp); } // 写，随后释放写锁

    // 读
    long stamp = stampedLock.tryOptimisticRead(); // 获得一个乐观读锁
    /* read data */
    if (!stampedLock.validate(stamp)) { // 检查：乐观读锁后，是否有其他写入。若有写入，则版本号变化，检查失败
        stamp = stampedLock.readLock(); // 检查失败：获取一个悲观读锁，重新读一次
        try { /* read data */ } finally { stampedLock.unlockRead(stamp); } // 读，随后释放悲观读锁
    }
```

# concurrent 包中的 synchronizer

`java.util.concurrent` 包含的，如下，都称为 synchronizer。可避免使用「lock + condition object + synchronized keyword」。 

- Condition (不是 `java.util.concurrent` 中的，而是 `java.util.concurrent.locks` 中的。<font color=red>严格说可能不算 synchronizer?</font>)
- Semaphore
- CyclicBarrier
- Phaser
- CountDownLatch
- Exchanger
- SynchronousQueue

# Condition (就是 condition variable)

wait-and-notify 机制是与特定对象及其上的锁是绑定在一起的，锁和唤醒对象不能分开，这在某些情况下不是很方便

更好的方法：jdk 1.5 提供的 Condition，与其它语言几乎一致的 condition variables 机制。只是方法名不同。对比：
- Java: `await()`, `signal()`, `signalAll()`
- C++: `wait()`, `notify_one()`, `notify_all()`

Condition 对象由 Lock.newCondition() 方法生成，从而允许一个 lock 产生多个 condition，可以根据实际情况来等待不同条件

与 c++ 类似，进入 wait 时自动释放锁，从 wait 返回时重新上锁。

例：task queue [代码](code/task-queue-using-cv.java) 生产者、消费者代码分开，看起来更清楚些

例：leet 1114 按序打印 [代码](code/leet-1114-print-in-order-using-cv.java)

# Semaphore

since java 1.5。可支持多个线程同时访问。特点：任何 thread 都可以 release；但通常希望最初上锁的 thread 才能 release。

```java
    private Semaphore sem = new Semaphore(3);

    public int getNextSequence() {
        try {
            sem.acquire();
            return super.getNextSequence();
        } catch (InterruptedException e) {
            // exception handling code
        } finally {
            sem.release();
        }
    }
```

# CountDownLatch

[例子，代码](code/CountDownLatchEx1.java)

- 1. 创建一个 latch：`CountDownLatch latch = new CountDownLatch(cnt)`
- 2. 创建 cnt 个工作线程
- 3. 每个线程内，工作完成后，调 `latch.countDown()`
- 4. 主线程中，`latch.await()` 等待 latch 计数降为 0，也就是等待所有工作线程结束。

我注：很像 c++ 中，最后所有 `t.join()`。

# CyclicBarrier

多个线程（parties）互相等，到一个称为 barrier point 的地点。

称为 cyclic，因为可复用。

意为「分片」而不是「计数器」，但其作用于「计数器」几乎一样。

「已经有指定数目的线程调用了 await()」，这个情况，称为 tripping the barrier。

使用方法：[例子，代码](code/CyclicBarrierEx1.java)
- 创建一个 cyclic barrier：`CyclicBarrier barrier = new CyclicBarrier(parties)`
- 创建 parties 个线程；每个线程内，工作完成后，调 `barrier.await()`，等待其他线程到达 barrier point
  - `barrier.await()` 的返回值，int 类型，表示：我是第几个完成的
- 主线程中，调每个线程的 `t.join()`，等待所有工作线程结束。然后收尾（if any）。

另一种方法：
- 创建时，多创建一个 `new CyclicBarrier(parties + 1)`
- 每个工作线程：与上面一样
- 主线程中，也用 `barrier.await()`，一起等。然后收尾（if any）。

还有一种方法：[例子，代码](code/CyclicBarrierDemo.java)
- 创建时，不多创建一个，但指定一个 runnable：`new CyclicBarrier(parties, new AggregatorThread())`。最后一个 trip the barrier 的线程将去执行该 runnable（就是原来主线程要做的事情）。
- 每个工作线程：与上面一样
- 单独定义步骤一中的 runnable AggregatorThread。其中
- 主线程中，只要启动各工作线程就行，不用操心 `t.join()`。收尾工作（if any）被最后一个完成的工作线程接着干了。

# Phaser

since java 1.7。取代了 CountDownLatch 和 CyclicBarrier。较难理解，但用起来容易。

[三者比较](https://www.javaspecialists.eu/archive/Issue257-CountDownLatch-vs-CyclicBarrier-vs-Phaser.html)

Phaser 的优点：
- 可动态指定线程数（parties 数量）。（对比 CountDownLatch：需在创建实例时指定 parties 数量，然后就不能改）
- 可以 set up Phaser in a tree to reduce contention。以另一个 Phaser 为 parent。（Latch 和 Barrier 无此功能）

一次运行可分为多个 phase，每个 phase 都可重用 Phaser 实例。每个 phase 里都可指定不同的 parties 数量。

- 每个线程要调用 `phaser.register()` 向 Phaser 实例注册自己
- 每个线程到达 barrier 时，要调用 `phaser.arriveAndAwaitAdvance()` 以通知 Phaser 并等待（故该方法是 blocking 的）。
- 到达的线程数 == 注册的线程数时，会进入下一个 phase，phase number 增加。`phaser.getPhase()` 返回当前 phase number。
- 若某线程完事，应调用 `phaser.arriveAndDeregister()` 通知 Phaser 该线程已完成，不再计入该 phase。

例：[代码](code/phaser-demo.java)

# SynchronousQueue 同步队列

名为 queue，其实不是。是多个多列之间交换数据的方法。这个「queue」中只能有一个元素！

只有两个方法：put() 和 take()。都是 blocking 的。put() 必须等到其他线程 take() 后才能返回；反之亦然。

例：[代码](code/SynchronousQueueIntegrationTest.java)

```java
    final SynchronousQueue<Integer> queue = new SynchronousQueue<>();
    // producer 线程中
    queue.put(producedElement);
    // consumer 线程中
    Integer consumedElement = queue.take();
```

# Exchanger

Exchanger 可被视为 SynchronousQueue 的双向形式

两个线程之间的数据交换。它提供一个同步点，在这个同步点，两个线程可以交换彼此的数据。这两个线程通过 exchange() 方法交换数据，当一个线程先执行 exchange() 方法后，它会一直等待第二个线程也执行 exchange() 方法，当这两个线程到达同步点时，这两个线程就可以交换数据了。

例：见这里：https://www.baeldung.com/java-exchanger

例：[代码](code/ExchangerTest.java)

# volatile 关键字

volatile的实现最终是加了内存屏障

- 保证写volatile变量会强制把CPU写缓存区的数据刷新到内存
- 读volatile变量时，使缓存失效，强制从内存中读取最新的值
- 由于内存屏障的存在，volatile变量还能阻止重排序

# 原子类型

多种类型，如 AtomicInteger、AtomicBoolean 等。都是 lock-free 及线程安全的。

```java
    private AtomicInteger x = new AtomicInteger();
    public void inc() {
        x.incrementAndGet();
    }
```

整数类型：
- 自增、自减：getAndIncrement(), incrementAndGet(), getAndDecrement(), decrementAndGet()
- 更新：`boolean compareAndSet(int expect_val, int update_val)`, `int getAndAdd(int delta)`, `int addAndGet(int delta)`

[用法示例：代码](code/AtomicTest.java)。用了 assert，运行时 `java -ea AtomicTest`。

## lazySet() vs. set()

AtomicInteger 中有一个被 volatile 关键字修饰的 value 成员属性。调用 set 方法为 value 设置新值后，立刻强制刷新到主内存中，不是仅先放在 cache 中。这样其他线程就会立即看见。

lazySet() 不是。lazySet() does not act as happens-before edges in the code.

何时需要用 lazySet()？


# 异步编程：概述

- by threads
- by Future
- by CompletableFuture
- by ListenableFuture (by Google Guava)

# Executor, ExecutorService 两个 interface

就是通常所说的 thread pool。

两者都是 interface。ExecutorService 继承自 Executor。提供的方法，用于任务提交和管理。

Executor 只有一个方法：`void execute(Runnable command)`。用法示例：

```java
    Executor executor = Executors.newSingleThreadExecutor();
    executor.execute(() -> System.out.println("Hello World"));
```

ExecutorService 的两个重要实现：
- ThreadPoolExecutor
- ScheduledThreadPoolExecutor

由 Executors 的静态方法创建：
- `newSingleThreadExecutor()`：仅单线程执行的线程池。
- `newFixedThreadPool()`：线程数固定的线程池；
- `newCachedThreadPool()`：线程数根据任务动态调整的线程池；
- `newScheduledThreadPool()`：可过一段时间执行，或周期性重复执行
- `newSingleThreadScheduledExecutor()`：结合 single thread 和 scheduled
- `newWorkStealingPool()`：用所有 available processors 作为其 target parallelism level

ExecutorService 可执行 Runnable 和 Callable 两种类型的 task。

把 task 分配给 ExecutorService 的方法：
- `void execute()`：无法得到执行结果，无法查看任务状态、是否执行完毕等。
- `Future<T> submit()`：返回该任务的 future
- `T invokeAny()`：任意执行一个任务，返回其结果
- `List<Future<T>> invokeAll()`：返回所有任务的 future list

关闭任务、关闭 thread pool：
- `shutdown()` 等正在执行的任务完成，再关闭
- `shutdownNow()` 立刻停止正在执行的任务
- `awaitTermination()` 等待指定的时间，再关闭

ExecutorService 的多种类型：

```java
    ExecutorService es = Executors.newFixedThreadPool(3); // 固定数目的
    es.submit(task1);
    // ...
    es.shutdown(); // 关闭线程池，不再接受新的任务

    // cached thread pool: 根据线程数量，动态调整池大小
    ExecutorService es = Executors.newCachedThreadPool();
    // 若想动态控制池子大小在 4 - 10 之间，得直接调用 ThreadPoolExecutor 的构造函数
    int min = 4, max = 10;
    ExecutorService es = new ThreadPoolExecutor(min, max, 60L, TimeUnit.SECONDS, new SynchronousQueue<Runnable>());
    
    // scheduled task
    ScheduledExecutorService ses = Executors.newSingleThreadScheduledExecutor();
    ScheduledExecutorService ses = Executors.newScheduledThreadPool(4);
    // 1秒后执行一次性任务:
    ses.schedule(new Task("one-time"), 1, TimeUnit.SECONDS);
    // 2秒后开始执行定时任务，每3秒执行:
    ses.scheduleAtFixedRate(new Task("fixed-rate"), 2, 3, TimeUnit.SECONDS);
    // 2秒后开始执行定时任务，以3秒为间隔执行:
    ses.scheduleWithFixedDelay(new Task("fixed-delay"), 2, 3, TimeUnit.SECONDS);
```

## ExecutorService vs. Fork/Join

java 7 引入 fork/join framework，用于并行计算。很多人用 fork/join 代替了 ExecutorService。其实还是各有各的优势。

fork/join framework
- 简单，性能好；但对 concurrent execution 的控制较少
- 最佳场景：可被递归分割成更小任务的任务

ExecutorService
- 更好控制：线程的数量、单个线程执行的任务粒度
- 最佳场景：独立的任务，one thread for one task

# by threads

创建 thread 的两种方式：

1. 继承 Thread 类，override 其 run() 方法。
  - 创建该类实例，并调用其 start() 方法。
2. 实现 Runnable 接口，实现其 run() 方法。
3. 实现 Callable 接口，实现其 call() 方法。
  - Runnable 和 Callable 都可用 thread 方法或 executor service 方法启动。

Thread 和 Runnable 的共同缺陷：执行完任务后，无法获取结果

解法：通过 Callable 和 Future (since Java 5), 可在任务执行完后，得到结果。

Callable，可以认为是增强版的 Runnable。表示一个待执行的 task。泛型接口。只有一个 call() 方法，返回类型就是泛型 V。

Runnable vs. Callable
- `Callable.call()` 有返回值，可用 Future 或 FutureTask 得到。`Runnable.run()` 无返回值，自然也无机制得到返回值。
- Callable 可抛出异常，Runnable 不能。
- Callable 需 `import java.util.concurrent.Callable`，Runnable 不需要。

Runnable 和 Callable 的两种用法：(1) 用 thread; (2) 用 executor service。

两种用法，[完整代码](code/runnable_callable_demo.java)

```java
// 以下用 Wrapper 表示：待执行的实际代码包装而成的 Runnable 或 Callable 类

// Runnable 用法一，用 thread 启动 task
    new Thread(new Wrapper(args)).start();

// Runnable 用法二，用 executor service 启动 task
    ExecutorService es = Executors.newSingleThreadExecutor();
    es.submit(new Wrapper(args)); // 不用管返回值
    es.shutdown();

// Callable 用法一，用 thread 启动 task，得到 future task 对象，再从中 get()
    Wrapper t = new Wrapper(args); // task 也可用 Callable<> 类型
    FutureTask<Integer> futureTask = new FutureTask<>(t);
    new Thread(futureTask).start(); // 启动线程
    Integer result = futureTask.get();

// Callable 用法二，用 executor service 提交 task，返回 Future 对象，再从中 get()
    ExecutorService es = Executors.newSingleThreadExecutor();
    Future<Integer> future = es.submit(new Wrapper(args));
    Integer result = future.get();
    es.shutdown();
```

# by Future

Futrue 是个接口。Future 就是对于具体的 Runnable 或者 Callable 任务的执行结果进行取消、查询是否完成、获取结果。必要时可以通过 get 方法获取执行结果，该方法会阻塞直到任务返回结果。

cancel(), isCancelled(), isDone(), get()

get() 是 blocking 的。所以要用多个线程同时进行，线程池里的线程数要足够。

例，使用 Future：[代码](code/square_calc_callable_future_demo.java)

实际做计算的 call()，用 lambda 实现。

```
Runnable   Future
   |         |
  RunnableFuture
        |
    FutureTask
```

FutureTask 既可以作为 Runnable 被线程执行，又可以作为 Future 得到 Callable 的返回值。


ForkJoinTask

to add later

# by CompletableFuture

```
    CompletableFuture (since Java 8)
	    implements Future, CompletionStage
```

是 Future 的演进（受 google Listenable Future 刺激）。可把多个 task 串在一起。You can use them to tell some worker thread to "go do some task X, and when you're done, go do this other thing using the result of X"。可使用某操作的结果，而不用阻塞线程地等该结果。

使用 thread pool
- 默认情况下，CompletableFuture 用 `ForkJoinPool.commonPool()` 作为它的线程池
- 也可自行提供 executor 作为 `supplyAsync()` 和 `runAsync()` 的第二个参数

简单用法

```java
    CompletableFuture<String> cf = CompletableFuture.supplyAsync(() -> "Hello");
    // ...
    String result = cf.get(); // 其值为 "Hello"
```

取结果，用 `get()` 或 `join()`。二者都 blocking 直至任务完成。区别：
- `get()`
  - 继承自 Future。为向后兼容。
  - 可一直等，也可设置 timeout
  - 抛出 checked exception，可能是 Interrupted、Execution 或 Timeout。（注意，checked exception 必须 declare 或 catch）
- `join()`
  - CompletableFuture 特有。推荐使用。
  - 只能一直等
  - 抛出 unchecked exception，是 CompletionException。（注意，unchecked exception 不需要 declare 或 catch）

异步计算阶乘，[完整代码](code/CompletableFutureTest.java)

```java
    int num = 12;
    CompletableFuture<Long> cf = CompletableFuture.supplyAsync(() -> factorial(num));
    while (!cf.isDone()) {
        System.out.println("CompletableFuture is not finished yet...");
    }
    long result = cf.join();
```

可以手动强行结束任务

```java
    CompletableFuture<String> cf = CompletableFuture.supplyAsync(() -> threadSleep()); // sleep 很长时间
    cf.complete("manually completed"); // 强行结束，并提供了一个返回值
    System.out.println("result: " + completableFuture.get()); // 输出人工提供的返回值 "manually completed"
    System.out.println("done? " + cf.isDone()); // 输出 True！人工强行结束，也是结束！
```

提交任务
- supplyAsync(): 有返回值
- runAsync(): 无返回值

任务正常完成后：
- `thenApply()`, `thenApplyAsync()`: 对任务结果做「转换」：以任务结果为输入，有返回值
- `thenAccept()`, `thenAcceptAsync()`: 对任务结果做「消费」：以任务结果为输入，无返回值
- `thenRun()`, `thenRunAsync()`: 执行一个额外任务，不依赖于任务结果：无输入，无返回值


两个操作串起来，前者的返回值作为后者的输入。`thenApply()` 貌似就是所谓 continuation。

```java
    ExecutorService exec = Executors.newSingleThreadExecutor(); // 自行提供 thread pool
    CompletableFuture<Integer> cf = CompletableFuture.supplyAsync(new MySupplier(), exec); // 自行提供 thread pool
    System.out.println(cf.isDone()); // False
    CompletableFuture<Integer> cf2 = cf.thenApply(new PlusOne());
    System.out.println(cf2.get()); // waits until the "calculation" is done, then prints 2

// 或简单点：
    CompletableFuture<Integer> cf = CompletableFuture.supplyAsync(new MySupplier())
            .thenApply(new PlusOne());
    Integer result = cf.get();
```

例：转换、消费

```java
    cf.thenApply(i -> { return "Processed " + i; })
      .thenAccept(i -> { System.out.println(i); });
```

合并多个 CompletableFuture，等它们全部完成、或其中任意一个完成：

- `allOf()`: 等所有完成
- `anyOf()`: 等任意一个完成

```java
    CompletableFuture<String> f1 = CompletableFuture.supplyAsync(() -> "Result 1");
    CompletableFuture<String> f2 = CompletableFuture.supplyAsync(() -> "Result 2");

// Void (注意不是 void) 类型。不处理「每个」返回值，也没有「合并」的返回值。
    CompletableFuture<Void> cf = CompletableFuture.allOf(f1, f2);
    cf.thenRun(() -> System.out.println("All tasks completed."));

// Void 类型。用 thenAccept()，处理「每个」返回值；但没有「合并」的返回值
    CompletableFuture.allOf(f1, f2, f3)
      .thenAccept(__ -> sayHelloToAll(f1.join(), f2.join(), f3.join()));

// String 类型。用 thenApply()，以「每个」返回值为输入，经运算得到「合并」的返回值
    CompletableFuture<String> names = CompletableFuture.allOf(f1, f2, f3)
      .thenApply(__ -> f1.join() + "," + f2.join() + "," + f3.join());

// 再加上 error handling
    CompletableFuture<String> names = CompletableFuture.allOf(f1, f2, f3)
      .thenApply(__ -> f1.join() + "," + f2.join() + "," + f3.join())
      .exceptionally(err -> {
          System.out.println("oops, there was a problem! " + err.getMessage());
          return "names not found!";
      });
```

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

vela 框架中，用了 ListenableFuture, 但取结果仍然用了 future.get(timeout, unit) 而不是 listener 方式。
它包装了 exception handling。
我要不要自己试试，直接用 get 而不用他包装了的 catchingOptional(get) 方式，看看 exception？

4个时间段并发，get() 后 set。
或，用 listener，自动set 数组相应的值。
如何处理超时？
initial idea: 包一个函数，这个函数的返回值为 future. future.get(timeout).

