# 线程间共享数据：用 mutex

主要避免 race condition 尤其是 data race

mutual exclusion

- std::mutex：独占的互斥量。等待 lock 堵塞地。
- std::timed_mutex：带超时的互斥量。等待 lock 最长一段时间。
- std::recursive_mutex：递归互斥量，可重入，不带超时功能
- std::recursive_timed_mutex：带超时的互斥量，可以递归使用

## mutex 互斥量、lock

mutex 是一个 synchronization object

通常有个全局 mutex；在各 thread 里调用其 lock() 和 unlock() 成员函数。

mutex 基本用法

```cpp
    mutex m; // 全局变量

    m.lock(); // 在 mutex 上获取 lock
    shared_var = get_var(); // 此处若抛出异常，则无法执行 m.unlock()，可能导致 deadlock
    m.unlock(); // 在 mutex 上释放 lock
```

通常不直接用，而是结合 lock_guard 或 unique_lock 使用。这些 lock，用 RAII 方式，方便 mutex 的使用。RAII「资源获取就是初始化」(resource acquisition is initialization)

- std::lock_guard，以 RAII 方式封装了 mutex，防止忘记 mutex.unlock() 或在调用 mutex.unlock() 之前抛出异常而导致无法调到 mutex.unlock()。基本上，lock_guard 构造时，会调用 mutex.lock()，析构时，会调用 mutex.unlock()。
- std::unique_lock，比 lock_guard 提供了更好的上锁和解锁控制，提供了 lock()、unlock()、try_lock() 等方式。除了在销毁时能自动解锁，平常也能通过 raii 容器来 lock/unlock 容器内的 mutex。
- std::shared_lock

std::lock() 函数，可对多个 mutex 和 lock_guard, unique_lock 等，以 atomic 方式一次性上多个锁。

std::lock() 可对任何 Lockable 对象上锁。Lockable 就是有 lock()、unlock()、try_lock() 成员函数的类型。

重大原则：所有对被保护数据的访问，都要遵循同样的保护方式。所以，被保护数据的指针或引用，不能（以返回值、函数参数等方式）传给其他不可控的调用者。

## lock_guard 基本用法

```cpp
    {
        mutex m, lock_guard<mutex> lg(m);
        shared_var = get_var();
    } // 出了此作用域，mutex.unlock() 在 lock_guard() 的析构函数中被调用
```

复杂一点的例子：[完整代码](code/list-protected-by-mutex.cpp)

```cpp
    // 为演示简单，被保护的数据、提供保护的 mutex，都是 global 变量
    // 实际，最好把二者封装在同一个类中
    std::list<int> l;
    std::mutex mtx;

    void add_to_list(int val) {
        lock_guard<mutex> lg{mtx};
        l.push_back(val);
    }
    bool list_contains(int val) {
        lock_guard<mutext> lg{mtx};
        return (l.end() != std::find(l.begin(), l.end(), val));
    }
```

## unique_lock 例

读取、写入数据时，给数据加锁；处理读出的数据时，不加锁。尽量减少锁的持有时间。

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

## deadlock

避免 deadlock 的关键：总是用同样的顺序 lock 两个 mutex。

exchange(T& obj1, T& obj2)

std::lock() 函数，可一次性 lock 两个或多个 mutex，而不会造成 deadlock。

例：交换两个 [代码](code/safe-swap.cpp)

(1) std::lock() 内部对两个 mtx 上锁时，任何一个都可能抛出异常。
    此时，std::lock() 会继续扩散该异常。
    若一个 lock 成功、另一个失败抛异常，则成功的那个也会自动 unlock，确保 all-or-nothing。

(2) adopt_lock 选项表示：(adopt: 收养)
      mtx 已经 lock 了，guard 应该 adopt the ownership of the existing lock on the mutex
      而不是 lock the mutex in the constructor

(3) c++17 提供了 scoped_lock，与 lock_guard<> 完全一样，但可以接受多个 mutex 作为参数。
    这一句可取代上面三句

所以，since c++17，以前用 std::lock() 的场景，都可以用 std::scoped_lock 代替。代码更少，更不易出错。

避免 deadlock 的一般原则：

- 避免 nested locks
- 持有一个 lock 时，避免调用别人提供的代码
- 按固定顺序 acquire locks
- 使用 lock hierarchy

## 管理多个 mutex：std::lock() vs. std::scoped_lock

- std::lock() 两种写法，顺序相反。
- std::scoped_lock 一句话就行，方便。有了它，就不用 std::lock() 了。

例子，安全交换，[代码](code/safe-swap-sol2.cpp)

```cpp
    friend void swap(T& a, T& b) {
        if (&a == &b) { return; } // 确保两个对象不同

    // 法一、法二顺序相反

    // 法一，先用 std::lock() 给两个 mutex 都上锁
    // 再用 lock_guard 来管理两个 mutex。用 adopt 方式，「收养」两个已上锁的 mutex。
    // 最后 lock_guard 析构时会自动给两个 mutex 解锁。
        std::lock(a.mtx, b.mtx);
        std::lock_guard<std::mutex> guard_a(a.mtx, std::adopt_lock);
        std::lock_guard<std::mutex> guard_b(b.mtx, std::adopt_lock);

    // 法二，先用 defer 方式用 lock_guard 来管理两个 mutex。defer 方式：创建 lock 后，mutex 并不上锁。
    // 再用 std::lock() 把它俩一起上锁。
    // 最后 unique_lock 析构时会自动给两个 mutex 解锁。
        std::unique_lock<std::mutex> ulock_a(a.mtx, std::defer_lock);
        std::unique_lock<std::mutex> ulock_b(b.mtx, std::defer_lock);
        std::lock(ulock_a, ulock_b);

    // 法三，用 scoped_lock，一句话就行。c++17 新特性
        std::scoped_lock guard(a.mtx, b.mtx);

        my_swap(a.some_detail, b.some_detail);
    }
```

unique_lock 并不总是拥有它对应的 mutex

初始化 unique_lock 时，第二个参数用 std::defer_lock 选项，表示：在构造期间，mutex 应处于 unlocked 状态。

晚点，有两种方式给 mutex 上锁：
- 调用 unique_lock.lock()（注意，不是调用 mutex.lock()）
- 把 unique_lock 对象传给 std::lock() 函数

（对比：std::adopt_lock 选项，让 the lock object 管理 the lock on a mutex）

unique_lock 保存「本 lock 是否拥有此 mutex」的标志。
它决定 unique_lock 的析构函数中实际要调用 unlock()。
可用 owns_lock() 查询。

与 lock_guard 相比，unique_lock 占用空间较大，性能也差些。所以尽量用 lock_guard 或 scoped_lock。

必须用 unique_lock 的场合：
- deferred locking
- lock 的所有权从一个 scope 转移到另一个

## 在 scope 之间转移 mutex 的 ownership

使用 move 语义；unique_lock 是 moveable 但不是 copyable 的。

场景：一个函数 lock mutex，然后把 lock 的所有权转给调用者

```cpp
    std::unique_lock<std::mutex> get_lock() {
        extern std::mutex some_mutex;
        std::unique_lock<std::mutex> ulock(some_mutex);
        prepare_data();
        return ulock; // 直接返回，不用显式调 std::move()
    }
    void process_data() {
        std::unique_lock<std::mutex> ulock(get_lock()); // 所有权转移
        do_something();
    }
```

更实际些的场景：lock 不是单独返回，而是作为某 gateway 对象的成员返回。所有数据访问都通过该 gateway 类。需访问数据时，获取一个 gateway 对象，也就获得了 lock。然后通过 gateway 对象的成员函数访问数据。完事后，销毁 gateway 对象，也就释放了 lock，其他线程就可以访问数据了。这样的 gateway 对象应该是 moveable 的，所以其中的 lock 成员也得是 moveable 的。

场景：在 unique_lock 对象被析构前，如果确认不再需要锁，可调用 unlock 主动提前释放锁。目的：提高性能。

## 只在初始化时保护共享数据

场景：初始化之后只读，或其他，所以只需要在 init 时保护

lazy initialization

```cpp
// 不太好，因为「检查资源是否已经初始化」也需要等
    std::shared_ptr<some_resource> resource_ptr;
    std::mutex resource_mutex;
    void foo() {
        std::unique_lock<std::mutex> ulock(resource_mutex); // 初始化前，lock
        if (!resource_ptr) {
            resource_ptr.reset(new some_resource);
        }
        ulock.unlock(); // 初始化完成，unlock
        resource_ptr->do_something();
    }
```

为了避免「检查资源是否已经初始化」也需要等，解法如下，臭名昭著的 double-checked locking 模式，还是不对，可能引起 race condition。


```cpp
    void undefined_behaviour_with_double_checked_locking() {
        if (!resource_ptr) { // 1
            std::lock_guard<std::mutex> ulock(resource_mutex);
            if (!resource_ptr) { // 2
                resource_ptr.reset(new some_resource); // 3
            }
        }
        resource_ptr->do_something(); // 4
    }
```

问题：没看太明白 p66，p79

解法：std::once_flag, std::call_once

```cpp
    std::shared_ptr<some_resource> resource_ptr;
    std::once_flag resource_flag;
    void init_resource() {
        resource_ptr.reset(new some_resource);
    }
    void foo() {
        std::call_once(resource_flag,init_resource); // 确保 init_resource() 只被调用一次，或者这里，或者以前别人调过
        resource_ptr->do_something();
    }
```

例

```cpp
    class X
    {
    private:
        connection_info connection_details;
        connection_handle connection;
        std::once_flag connection_init_flag;
        void open_connection() {
            connection = connection_manager.open(connection_details);
        }
        X(connection_info const& c_): connection_details(c_) {}
    
        void send_data(data_packet const& data) { // 1
            std::call_once(connection_init_flag, &X::open_connection, this); // 2
            connection.send_data(data);
        }
    
        data_packet receive_data() { // 3
            std::call_once(connection_init_flag, &X::open_connection, this); // 2
            return connection.receive_data();
        }
    };
```

跟 std::mutex 一样，std::once_flag 对象既不是 copyable，也不是 moveable。

static 的 local 变量，其初始化发生在 control path 第一次经过其 declaration 时。c++11 之前，可能有 race condition，多个线程都可能认为自己先经过。c++11 之后，确保了其唯一性。所以，有些场景下，可用 static 变量来代替 call_once。单例模式，single global instance.

```cpp
    class my_class;
    my_class& get_instance() {
        static my_class instance; // c++11 之后，其初始化绝对是 thread-safe 的
        return instance;
    }
```

「只在初始化时保护数据」是「很少更新的数据」的特殊情况。后者见下。

## read-write mutex 读写锁

适用场景：读操作远远多于写操作。典型应用：多线程共享的 cache

std::shared_mutex (since c++17)
- write：调用 lock()
- read：调用 lock_shared()

std::shared_lock (since c++14)，以 raii 方式管理 std::shared_mutex
- 构造时：尝试以 lock_shared() 锁住传入的 mutex
- 析构时：确保以 unlock_shared() 的方式释放 mutex
- 平时：可使用 lock() 和 unlock()，以「共享方式」获取和释放 mutex

reader-writer lock 读写锁，用 std::shared_mutex 和 std::shared_lock 实现
- std::shared_mutex 或 std::shared_timed_mutex，结合 std::shared_lock
- reader/writer 用同一个 mutex 对象
- writer: 还用普通的 std::lock_guard 或 std::unique_lock
- reader: 用 std::shared_lock

例：电话本 [代码](code/rw-telebook.cpp)

例：dns cache [代码](code/rw-dns-cache.cpp)
