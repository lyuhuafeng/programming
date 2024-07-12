
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

# spinlock

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

很相似，区别主要在使用场景上：

semaphore
- 资源数量是有限整数，方便用 semaphore 来控制访问
- 本质上是个 counter + mutex + wait queue

condition variable
- 适合 event-driven 的场景
- 本质上是个 wait-queue，支持 block-wait 和 wakeup 操作

