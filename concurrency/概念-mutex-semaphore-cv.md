
目录

- lock vs. mutex
- spinlock
- lock/mutex vs. semaphore
- lock/mutex 可重入
- lock/mutex shared
- lock vs. binary semaphore
- semaphore vs. binary semaphore
- semaphore vs. condition variable

# lock vs. mutex

从概念上，没本质区别。

# spinlock vs. mutex

https://stackoverflow.com/questions/5869825/when-should-one-use-a-spinlock-instead-of-mutex

概念上：
- mutex: 若拿不到，则线程进入 sleep（则其他线程可以运行），直到被 wake up（因为 lock 被其他线程释放）
- spinlock: 若拿不到，并不 sleep，而是不停重试，直到拿到。（不 sleep，则其他线程不能运行，直到本线程的时间额度用完，os 强制切换线程）

问题：
- mutex: 线程进入 sleep 和被 wake up，都开销大。在多核/多 cpu 系统上，若锁很多，且持有锁时间都短，则 sleep/wake 开销大。
- spinlock: 无需 sleep/wake，但不停重试，也浪费 cpu。
  - 在单核/单 cpu 系统上，spinlock 无太大意义，因为在本线程未用尽时间额度时，其他线程无法运行，也就无法释放 spinlock 试图获得的锁。
  - 有些 os（如 ios），线程调度器不能保证低优先级的线程被调度运行。如果某低优先线程拿到了 spinlock，未释放就用尽时间额度，停止运行；后续也未有机会运行，无机会释放 spinlock，可能导致永久性死锁。解法：ios 的 os_unfair_lock。

实际：
- 多数 os 不严格区分二者。
- 多数 os 使用 hybrid mutex 和 hybrid spinlock。
  - hybrid mutex: 若没拿到，先 spin，若干时间或若干重试后，再 sleep。也称为 adaptive mutex，如 POSIX 的 PTHREAD_MUTEX_ADAPTIVE_NP、Win32 的 SetCriticalSectionSpinCount。
  - hybrid spinlock: 若没拿到，先 spin，若干时间后可主动 yield 已让其他线程运行。

编程：
先用 mutex

A lock which uses busy waiting. (The acquiring of the lock is made by xchg or similar atomic operations).

# lock/mutex vs. semaphore

概念上，
- mutex 是保护 shared data 的机制。保证我独占式地访问资源。我访问过程中，别人访问不了，从而不会破坏资源。
- semaphore 是 signaling 机制，用于 synzhronization（各任务的顺序）。典型场景：producer-consumer。

但 https://crystal.uta.edu/~ylei/cse6324/data/semaphore.pdf 提到，
- semaphore 可同时提供 mutex 和 conditional sync.
- Counting Semaphore: can be used for mutual exclusion and conditional synchronization.
- binary semaphore: 特意用来 mutual exclusion 的。

用法
- mutex：一人独占地访问某资源。我 lock，我 unlock。每个「人」都做这两个操作，按同样顺序。
- semaphore：一人给另一人发 signal。我 signal，你 wait。每个人只做其中一个操作。

ownership
- mutex 通常有 ownership 的概念。我 lock，然后也只能我 unlock。
- semaphore 通常没有 ownership 的概念。A binary semaphore can be signaled by any thread (or process).

# lock/mutex 可重入

re-entrant lock 可重入的锁，或称 recursive mutex 递归的: 我以前拿到的 lock，我还能再次拿到。前提：lock/mutex 的 ownership 概念。

本来 lock/mutex 从概念上是可以被 owner 多次 lock 的，也就是，本来就是「可重入的」。但，具体实现上，又搞出了 reentrant 和 non reentrant 的

可重入的 re-entrant, recursive
- java synchronized 关键字的锁
- java ReentrantLock
- c++ std::recursive_mutex

不可重入的 non re-entrant, non-recursive
- java: ?
- c++ std::mutex

# lock/mutex shared

本来 lock/mutex 从定义上就不是 shared 的。但 c++ 搞出了 std::shared_mutex

- c++ std::shared_mutex

有两个 access level
- shared - several threads can share ownership of the same mutex.
- exclusive - only one thread can own the mutex.

- 若某线程拿到了 exclusive lock，则其他线程不能拿到该 lock（即使是 shared）
- 若某线程拿到了 shared lock，则其他线程不能拿到其 exclusive lock，但仍可拿到 shared lock
- 一个线程内，同时只能拿到一个 lock（shared or exclusive）。<font color=red>是「不可重入」？</font>

主要用于「一写多读」的场景。

# lock vs. binary semaphore

- V: 增大; signal; release; up
- P: 减小; wait;   acquire; down

如何记忆：V 可以是 victory，胜利了自然就增大了，就可以发 signal 给别人了。

binary semaphore
- 连续的 P 操作会被 block 住
- P、V 可由不同人操作（来自 ownership 的概念）

lock/mutex
- lock 的 owner 还可继续 lock（定义上，天然可重入）
- lock 与 unlock 由同一 thread 发出（来自 ownership 的概念）

区别主要来自 ownership。

# semaphore vs. binary semaphore


# semaphore vs. condition variable

都是 signaling/synchronization 机制。

semaphore 初始化为 0，就可 block 住 acquire 操作，直到其他线程 release 从而 signal 它。

semaphore 可代替 condition variable，且性能更好。

很相似，区别主要在使用场景上：

semaphore
- 资源数量是有限整数，方便用 semaphore 来控制访问
- 本质上是个 counter + mutex + wait queue

condition variable
- 适合 event-driven 的场景
- 本质上是个 wait-queue，支持 block-wait 和 wakeup 操作

# latch, barrier

英语学习：latch n. 门闩；碰锁；弹簧锁

数字电路中，latch 锁存器、闩锁

- c++ std::latch = java 里的 CountDownLatch
- c++ std::barrier = java 里的 CyclicBarrier

两者都是让一些线程 block 住，直到某个 counter 变为 0。

所做工作都可用 cv、thread 等完成。但更方便、性能通常更好。内部机制通常是 lock-free 的。

latch
- 只可用一次
- to manage one task by multiple threads

barrier
- 可用多次
- to manage repeated tasks by multiple threads
- 可在 completion step 时执行一个函数。(completion step: counter 变为 0 的状态)

boss-worker 场景：
- 用 latch: [代码](code/boss-worker-latch-demo.cpp)，简化版 [代码](code/boss-worker-latch-simplified-demo.cpp)
- 用 semaphore: [代码](code/boss-worker-semaphore-demo.cpp)  work: 每个工人 release(1)，boss 等待所有 worker 完事则要 acquire(6)；回家，每个 worker 要 acquire(1)，但 boss 要给每个 worker 一个，共 release(6)。逻辑上不如 latch 直接。但代码还行。
- 用 cv：[代码](code/boss-worker-cv-demo.cpp) 代码确实比 semaphore 麻烦，比 latch 就更麻烦了。
- 用 barrier: [代码](code/boss-worker-barrier-demo.cpp)

barrier vs. memory barrier (fence)

posix-style: pthread_barrier_wait ... since around 2000

Memory barriers and POSIX-style barriers are semantically related; both mechanisms ensure that certain events are not re-ordered between adjacent phases; they stay on their side of the barrier.

Apparently databases historically call shared-memory locks "latches" to distinguish them from locks used for transaction conflict detection.

The full name is typically CountDownLatch [0]. The latch still has 2 states, closed and open.

latches can be edge or level triggered. The important concept is that once they are triggered, they latch the input value, and maintain it after the input has disappeared. That's what std::latch does... Once triggered it's always triggered. Same as Java's CountDownLatch