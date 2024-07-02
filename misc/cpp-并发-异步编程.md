## thread 用法

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
    class ThreadGuard {
    private:
        std::thread& t_;
    public:
        explicit ThreadGuard(std::thread& t) : t_(t) {}
        ~ThreadGuard() {
            if (t_.joinable()) {
                t_.join();
            }
        }
        ThreadGuard(const ThreadGuard&) = delete;
        ThreadGuard& operator=(const ThreadGuard&) = delete;
    };

    void do_something();

    void show() {
        std::thread wk_thread;
        ThreadGuard g{wk_thread};
        wk_thread = std::thread{do_something};
        do_domething_in_current_thread();
        return;
    }
```

## mutex 互斥量、lock

mutual exclusion

- std::mutex：独占的互斥量。等待 lock 堵塞地。
- std::timed_mutex：带超时的互斥量。等待 lock 最长一段时间。
- std::recursive_mutex：递归互斥量，可重入，不带超时功能
- std::recursive_timed_mutex：带超时的互斥量，可以递归使用

mutex 是一个 synchronization object

通常有个全局 mutex；在各 thread 里调用其 lock() 和 unlock() 成员函数。

- std::lock_guard，以 RAII 方式封装了 mutex，防止忘记 mutex.unlock() 或在调用 mutex.unlock() 之前抛出异常而导致无法调到 mutex.unlock()。基本上，lock_guard 构造时，会调用 mutex.lock()，析构时，会调用 mutex.unlock()。
- std::unique_lock，比 lock_guard 提供了更好的上锁和解锁控制，提供了 lock()、unlock()、try_lock() 等方式。除了在销毁时能自动解锁，平常也能通过 raii 容器来 lock/unlock 容器内的 mutex。
- std::shared_lock

RAII，也称为「资源获取就是初始化」(Resource Acquisition Is Initialization)

重大原则：所有对被保护数据的访问，都要遵循同样的保护方式。所以，被保护数据的指针或引用，不能（以返回值、函数参数等方式）传给其他不可控的调用者。

mutex 基本用法
```cpp
    mutex m;
    m.lock(); // 在 mutex 上获取 lock
    shared_var = get_var(); // 此处若抛出异常，则无法执行 m.unlock()，可能导致 deadlock
    m.unlock(); // 在 mutex 上释放 lock
```

lock_guard 基本用法
```cpp
    {
        mutex m, lock_guard<mutex> lg(m);
        shared_var = get_var();
    }
```

复杂一点的例子

```cpp
    // 为演示简单，被保护的数据、提供保护的 mutex，都是 global 变量
    // 实际，最好把二者封装在同一个类中
    std::list<int> data_list;               // 1.
    std::mutex data_mutex;                  // 2.

    void add_to_list(int val) {
        lock_guard<mutex> lg{data_mutex};    // 3.
        data_list.push_back(val);
    }
    bool list_contains(int val) {
        lock_guard<mutext> lg{data_mutex};    // 4.
        return (data_list.end() != std::find(data_list.begin(), data_list.end(), val));
    }
```

unique_lock 例：读取、写入数据时，给数据加锁；处理读出的数据时，不加锁。尽量减少锁的持有时间。

```cpp
    void get_process_write() {
        std::unique_lock<std::mutex> lk(a_mutex);   // 1.
        Data chunk = get_data_chunk();
        lk.unlock();                                // 2.
        Result res = process_data_chunk(chunk);
        lk.lock();                                  // 3.
        write_back(chunk, res);
    }
```

## 读写锁

适用场景：读操作远远多于写操作。典型应用：多线程共享的 cache

shared_mutex (since c++17)
- write：调用 lock()
- read：调用 lock_shared()

shared_lock (since c++14)
- 构造时：尝试以 lock_shared() 锁住传入的 mutex
- 析构时：确保以 unlock_shared() 的方式释放 mutex
- 平时：可使用 lock() 和 unlock()，以「共享方式」获取和释放 mutex

例：dns cache

```cpp
    class DNSEntry;

    class DNSCache {
    public:
        typedef unordered_map<string, DNSEntry> RecMap;

    private:
        RecMap entries_;
        mutable shared_mutex entry_mutex_;                     // 1.

    public:
        DNSEntry find_entry(const string& domain) const {
            shared_lock<shared_mutex> slk(entry_mutex_);  // 2.
            const RecMap::const_iterator target = entries_.find(domain);
            return (target != entries_.end()) ? target->second : DNSEntry();
        }
        void update_one_entry(const string& domain, const DNSEntry& entry) {
            unique_lock<shared_mutex> ulk(entry_mutex_);  // 3.
            entries_[domain] = entry;
            return;
        }
    };
```

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

## std::condition_variable

条件变量是c++11引入的一种同步机制，它可以阻塞一个线程或者个线程，直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁配合使用，这里的锁就是上面介绍的std::unique_lock。

condition_variable（条件变量）是 C++11 中提供的一种多线程同步机制，它允许一个或多个线程等待另一个线程发出通知，以便能够有效地进行线程同步。

condition_variable 需要与 mutex（互斥锁）一起使用。当线程需要等待某个条件变成真时，它会获取一个互斥锁，然后在条件变量上等待，等待期间会自动释放互斥锁。另一个线程在满足条件后会获取相同的互斥锁，并调用条件变量的 notify_one() 或 notify_all() 函数来唤醒等待的线程。

## 原子变量 std::atomic

`std::atomic<T>`。就不需要用 std::mutex 来保护该变量了，可在各线程中直接使用。

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


## 异步操作：future、promise

- promise: 代表 producer/write 端，used by the producer to set (and "send") the data
- future: 代表 consumer/read 端，used by "consumer" to receive the data

future 封装的是一种访问异步操作的「机制」，也是一种线程间的同步手段。

用来收取一个异步操作的、尚未算完的结果。

- 在一个线程（creator）中创建一个「异步操作」（通常就是创建了一个新的线程，执行操作）
  - 如何创建：通过 std::async，std::packaged_task 或者 std::promise 等方式
- 该「异步操作」返回一个 future 对象给 creator，供其访问「异步操作」的状态、结果等。
  - get(): 来等待异步操作结束并返回结果，是一个阻塞过程
  - get() 之前，最好确保计算已完成、结果已经可以读取。如何做？
    - valid(): checks if the future has a shared state.
    - wait(): 等待异步操作结束，也是一个阻塞过程
    - wait_for()、wait_until(): 等一段时间
    - 各种 wait() 的返回结果是三种状态之一：`future_status::ready`、`future_status::timeout`(还没 ready)、`future_status::deferred`(计算还没开始)

future 和 promise 间的关系，最简示例
```cpp
    std::promise<int> p;                 // produce/write 端
    std::future<int> f = p.get_future(); // consume/read 端
    p.set_value(15);   // 向 promise 中写入数据
    int val = f.get(); // 从 future 中读取结果
```

与 thread 配合使用，场景一：一个 thread 异步在 promise 中写结果；直接从 future 中读结果。

```cpp
int foo(int x) { return x + 1; }

int main() {
    std::promise<int> p;                 // produce/write 端
    std::future<int> f = p.get_future(); // consume/read 端
    std::thread t([&p] (int x) { p.set_value(foo(x)); }, 5); // write 端：异步调用 foo(x) 并将结果放入
    std::cout << f.get() << std::endl;   // read 端：从 future 中读取结果
    t.join();
    return 0;
}
```

与 thread 配合使用，场景二：一个 thread 从 future 中读结果；直接在 promise 中写结果（供 future 读）

```cpp
void func(/* const */ std::future<int>& f) { // 不能加 const
    int val = f.get();
    printf("val:%d\n", val);
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(func, std::ref(f));
    p.set_value(144);
    t.join();
    return 0;
}
```

## packaged_task

packaged_task 把各种 callable 对象包装成可异步调用的对象，执行结果通过与其相联系的 future 对象读取。

packaged_task 是连数据操作创建都封装进去了的 promise

packaged_task 对象内部包含了两个最基本元素，
- 被包装的任务(stored task)。这里 task 就是一个 callable 对象。
- 共享状态(shared state)，用于保存任务的返回值，可以通过 std::future 对象读取

```cpp
// 包装一个 function。两种启动方式：非异步、异步（通过 thread）
    int my_add(int x, int y) { return x + y; }

    std::packaged_task<int(int,int)> task(my_add); // 包装一个 function
    future<int> f = task.get_future();

    task(40, 8); // 像普通函数一样启动任务，非异步，调用的是 my_add(40, 8)
    int res = f.get(); // 阻塞等待任务结束，并读取结果
    
    task.reset(); // 重置 shared state
    f = task.get_future();

    thread t(move(task), 22, 10); // 通过 thread 异步启动 task
    t.join();
    int res = f.get();

// 包装一个 lambda。非异步启动。
    packaged_task<int(int,int)> task([](int a, int b) { return a + b; }); // 包装一个 lambda
    task(62, 10);
    future<int> f = task.get_future();
    int val = f.get();
```

## async

把 future、promise 和 packaged_task 封装了起来。代码最简洁。

```cpp
    #include <future> // std::async()

    int func(int i) { return i + 1; }

    std::future<int> f = std::async(func, 6);
    int res = f.get(); // 堵塞直到 func() 返回
```

另一个例子：
```cpp
    int return_two() { return 2; }

    future<int> f = async(launch::async, return_two);
    if (f.valid()) { cout << f.get() << endl; }
    else { cout << "invalid state" << endl; }
```
