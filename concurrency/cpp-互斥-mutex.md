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

通常不直接用，而是结合 lock_guard 或 unique_lock 使用。

- std::lock_guard，以 RAII 方式封装了 mutex，防止忘记 mutex.unlock() 或在调用 mutex.unlock() 之前抛出异常而导致无法调到 mutex.unlock()。基本上，lock_guard 构造时，会调用 mutex.lock()，析构时，会调用 mutex.unlock()。
- std::unique_lock，比 lock_guard 提供了更好的上锁和解锁控制，提供了 lock()、unlock()、try_lock() 等方式。除了在销毁时能自动解锁，平常也能通过 raii 容器来 lock/unlock 容器内的 mutex。
- std::shared_lock

RAII，也称为「资源获取就是初始化」(resource acquisition is initialization)

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

## stack 的问题

std::stack 在多线程环境下的问题。api interface 设计缺陷。

- empty() 和 size() 不可靠。常见用法 `if (!st.empty()) { st.pop() 或 t = st.top(); }`。若在调用 empty() 和 pop() 之间，另一个线程做了 pop()，则出错。
- 常见用法 `t = st.top(); st.pop();`。两个线程都如此操作，可能两个 top() 拿到同样内容，两个 pop() 弹出两个不同元素，其中一个其实未被读到就被扔了。

解法：结合 top 和 pop 为一（poptop()）。问题：若对象的 copy constructor 可抛出异常，则 pop_top() 可能有问题。例，stack<vector<int>>。复制 vector 时，若分配内存失败，则 vector 的 copy constructor 可能抛出 bad_alloc 异常。新的 pop_top() 函数，先修改 stack (pop)，再把弹出的 vector 返回。若 pop 成功，但把弹出的 vector 拷贝赋值以待返回时，抛出上述异常，则弹出的数据就丢失了。
... 没看太明白, to check later.

option 1: 传入引用 `vector<int> res; st.pop(res)`。问题：凭空构建一个 object 可能很贵甚至不可能；很多自定义对象不支持 assignment.

option 2：要求不抛出异常的 copy/move constructor。问题：受限制

option 3：返回指向被弹出元素的指针，而不是 by value，然后就可以安全 copy。问题：需要自己管理内存，开销很大（尤其是基本类型如 integer）。但若用此方法，应使用 shared_ptr，可避免内存泄漏。

option 4：结合 2,3. [代码](code/thread-safe-stack.cpp)

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

## std::unique_lock 比 std::lock_guard 更灵活

unique_lock 并不总是拥有它对应的 mutex

初始化 unique_lock 时，第二个参数用 std::defer_lock 选项，表示：在构造期间，mutex 应处于 unlocked 状态。
晚点，有两种方式给 mutex 上锁：
- 调用 unique_lock.lock()（注意，不是调用 mutex.lock()）
- 把 unique_lock 对象传给 std::lock() 函数

（对比：std::adopt_lock 选项，让 the lock object 管理 the lock on a mutex）

例子，安全交换，[代码](code/safe-swap-sol2.cpp)

对比三种写法：

```cpp
    friend void swap(T& lhs, T& rhs) {
        if (&lhs == &rhs) { return; } // 确保两个对象不同

        // 法一，先 lock 两个 mutex，再用两次 lock_guard
        lock(lhs.mtx, rhs.mtx);
        lock_guard<mutex> guard_a(lhs.mtx, adopt_lock);
        lock_guard<mutex> guard_b(rhs.mtx, adopt_lock);

        // 法二，用 scoped_lock，一句话就行。c++17 新特性
        scoped_lock guard(lhs.mtx, rhs.mtx);

        // 法三，先用两次 unique_lock(defer_lock)，再用 lock
        unique_lock<mutex> ulock_a(lhs.mtx, defer_lock);
        unique_lock<mutex> ulock_b(rhs.mtx, defer_lock);
        lock(ulock_a, ulock_b);

        my_swap(lhs.some_detail, rhs.some_detail);
    }
```

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

更实际些的场景：lock 不是单独返回，而是作为某 gateway 对象的成员返回。所有数据访问都通过该 gatewa 类。需访问数据时，获取一个 gateway 对象，也就获得了 lock。然后通过 gateway 对象的成员函数访问数据。完事后，销毁 gateway 对象，也就释放了 lock，其他线程就可以访问数据了。这样的 gateway 对象应该是 moveable 的，所以其中的 lock 成员也得是 moveable 的。

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
            connection=connection_manager.open(connection_details);
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

shared_mutex (since c++17)
- write：调用 lock()
- read：调用 lock_shared()

shared_lock (since c++14)
- 构造时：尝试以 lock_shared() 锁住传入的 mutex
- 析构时：确保以 unlock_shared() 的方式释放 mutex
- 平时：可使用 lock() 和 unlock()，以「共享方式」获取和释放 mutex

例：dns cache

```cpp
    class dns_entry;

    class dns_cache {
    public:
        typedef unordered_map<string, dns_entry> dns_map;

    private:
        dns_map entries_;
        mutable shared_mutex mtx_;                     // 1.

    public:
        dns_entry find_entry(const string& domain) const {
            shared_lock<shared_mutex> slock(mtx_);  // 2.
            const dns_map::const_iterator it = entries_.find(domain);
            return (it != entries_.end()) ? it->second : dns_entry();
        }
        void update_one_entry(const string& domain, const dns_entry& entry) {
            lock_guard<shared_mutex> guard(mtx_);  // 3.
            entries_[domain] = entry;
        }
    };
```
