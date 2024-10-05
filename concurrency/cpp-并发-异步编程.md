
## overview

memory model
- atomics

multithreading
- threads
- 用于 shared data 的 synchronization primitives
  - mutex 和 lock
  - condition variable
  - semaphore (c++20)
  - latch, barries (c++20)
- thread-local data: 显式声明为 thread-local，每个 thread 都有其 copy，就没有 shared data 了。
- tasks

- cooperative interruption (c++20)
- synchronized outputstreams (c++20)

英语学习：latch n. 门闩；碰锁；弹簧锁

## semaphore

与 mutex 基本类似，但可以允许最多 x 个 thread 同时进入 critical section，且可以设置超时时间。

since c++20, too new

- std::counting_semaphore
- std::binary_semaphore

## Spin-lock

(aka Spinlock)= A lock which uses busy waiting. (The acquiring of the lock is made by xchg or similar atomic operations).

## 函数

std::lock，可以同时对多个互斥量上锁。
std::try_lock，尝试同时对多个互斥量上锁。
std::call_once，如果多个线程需要同时调用某个函数，call_once 可以保证多个线程对该函数只调用一次。

```cpp
    std::mutex foo, bar;

    void task_a() {
        std::lock(foo, bar); // 取代 foo.lock(); bar.lock();
        std::cout << "task a\n";
        foo.unlock();
        bar.unlock();
    }
```


## 原子变量 std::atomic

目的：在不同线程间，同步内存访问

痛点：多个线程共享一个简单类型的变量（int，bool，pointer等），对这种简单临界资源的访问，如有两个线程，对一个变量进行操作，一个线程读这个变量的值，一个线程往这个变量中写值。即使是一个简单变量的读取和写入操作，如果不加锁，也有可能会导致读写值混乱（因为一条语句可能会被拆成3、4条汇编语句来执行，所以仍然有可能混乱）。正常情况下，我们想到就是使用std::mutex来解决上述对临界资源访问的问题，使用std::mutex程序执行不会导致混乱，但是每一次循环都要加锁解锁是的程序开销很大。

原子类型是无锁类型，但是无锁不代表无需等待，因为原子类型内部使用了 CAS 循环，当大量的冲突发生时，该等待还是得等待！但是总归比锁要好。

CAS 全称是 Compare and swap, 它通过一条指令读取指定的内存地址，然后判断其中的值是否等于给定的前置值，如果相等，则将其修改为新的值




atomic_flag，是 bool 类型。

- 不像 atomic<T>，atomic_flag 是 guaranteed to be lock-free. （什么意思？使用时绝对用不着 lock？内部实现绝对没用到 lock？）
- 不像 atomic<bool>, atomic_flag 没提供 load() 和 store() 操作。

since c++11。c++ 11 提供了
- 构造函数: 
  - since c++11, before c++20: 唯一初始化方法：`atomic_flag f = ATOMIC_FLAG_INIT`，保证初始化为 cleared，也就是 false。
  - c++ 20 后，缺省初始化 `atomic_flat v` 就行，不再需要 `ATOMIC_FLAG_INIT`
- clear(): 设为 false
- test_and_set(): 设为 true 并返回以前的值


类型定义如下：
```cpp
    template <class T>
    struct atomic;
```

用法：`atomic<T>`。就不需要用 std::mutex 来保护该变量了，可在各线程中直接使用。

```cpp
    std::atomic<int> i(3); // 初始化
    int val = i.load(); // 读取
    i.store(42); // 赋值
    i.fetch_add(5); // 加法 i+=5
    i.fetch_sub(3); // 减法 i-=3
    const int current = i.exchange(next); // 赋值并返回原值
    compare_exchange_weak
    compare_exchange_strong

    // 计数器
    atomic<int> counter(0); // 全局计数器
    counter.fetch_add(1); // 线程 1 中，计数器加一
    counter.fetch_sub(1); // 线程 2 中，计数器减一

    // spinlock
    std::atomic<bool> lock(false);  // initialize to false
    { // some critical section, trying to get the lock:
        while (lock.exchange(true)) { }  // now we have the lock
        /* do stuff */
        lock = false; // release lock
    }
```

