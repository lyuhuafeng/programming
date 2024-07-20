## thread(c++ 11), jthread (c++20)

jthread 在生命结束或抛出异常时可自动 join。从而不用自己用 raii 方式封装 thread。

### thread

基本用法。注意 thread 对象构造后，要调用 t.join() 或 t.detach()。

```cpp
    class tag_node { int a; int b; };
    void func(tag_node node) { ... }
    void func2(tag_node &node) { ... }

	tag_node node;

	// 函数参数是 value 类型，传 value 或传 reference 都可正常运行，但没有改变 node 内容
	thread t(func, node);
	thread t(func, ref(node));
	tag_node& n2 = node;
	thread t(func, n2);
	thread t(func, ref(n2));
	t.join();

	// 函数参数是 reference 类型，传 value 则编译报错，传 reference 可正常运行，且改变了 node 内容
	// thread t(func2, node); // 编译出错
	// thread t(func2, n2); // 编译出错
    thread t(func2, ref(node)); // 正确
    thread t(func2, ref(n2));   // 正确：n2 已经是个 reference，但也要用 ref()
	t.join();
```

raii 用法

```cpp
    class thread_guard {
    private:
        std::thread& t_;
    public:
        explicit thread_guard(std::thread& t) : t_(t) {}
        ~thread_guard() {
            if (t_.joinable()) {
                t_.join();
            }
        }
        thread_guard(const thread_guard&) = delete;
        thread_guard& operator=(const thread_guard&) = delete;
    };

    void do_something(int local_status);

    void show() {
        int local_status = 0;
        std::thread t = std::thread{do_something, local_status};
        thread_guard g{t};
        do_domething_in_current_thread();
        // g 析构时，会调用 t.join()
    }
```

thread 用类的（非静态）成员函数，函数名要用 `&class_name::func_name`，所有参数之前还要多加一个「类对象的地址」参数。

- 若在类内调用，`thread(&class_name::func_name, this, arg1, arg2)`
- 若在类外调用，`thread(&class_name::func_name, &class_inst, arg1, arg2)`

[完整代码](code/thread-using-class-member-func.cpp)

### jthread

to add

## overview

- mutex, lock, lock()
- condition variable
- cooperative interruption (c++20)
- semaphores (c++20)
- latches, barriers (c++20)
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

