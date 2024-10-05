## thread (c++ 11), jthread (c++20)

jthread 在生命结束或抛出异常时可自动 join。从而不用自己用 raii 方式封装 thread。

### thread

基本用法。注意 thread 对象构造后，要调用 `t.join()` 或 `t.detach()`。

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

- 若在类内调用，`thread(&class_name::func_name, this, arg1, arg2)`。「类对象的地址」是 this。
- 若在类外调用，`thread(&class_name::func_name, &class_inst, arg1, arg2)`。「类对象的地址」是 &class_inst。

[完整代码](code/thread-using-class-member-func.cpp) 内含 `std::bind()` 的用法说明。

### jthread

to add

### thread 的返回值

上面介绍的用法，对 thread 是「发射后不管」的（fire-and-forget），或者「发射后无法管」，无法拿到其返回值。

（更严格地说，再 detach 一下，才是真正的「不管」：`std::thread([](){ run_async_task(); }).detach();`。）

如何得到返回值？

法一：用 promise/future。在 thread 中，把结果放到 promise 中，在 thread 外从相应的 future 里读。例：[代码](code/thread-result-by-future-promise.cpp)，[promise-future-div-prod.cpp](code/promise-future-div-prod.cpp)

```cpp
    // 注意 move 语义，两个 &
    void func(std::promise<int> && p) { p.set_value(17); }

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(func, std::move(p)); // 必须用 move()
    t.join();
    int i = f.get();
```

法二：用 async 结合 future，不用 promise，连 thread 都不用了。

```cpp
    int func() { return 17; }
    std::future<int> ret = std::async(&func);
    int i = ret.get();
```
## task 机制

task 机制，可以认为是 future 和 promise 之间的 data channel

三个变种
- asynchronous function call: std::async
- 一个 callable 对象的简单 wrapper: std::packaged_task
- 显式的一对: std::future 和 std::promise

```cpp
// 使用 thread
    int res;
    std::thread t([&]{ res = 3 + 4; });
    t.join();
    // res 已被赋值

// 使用 task 的 async
    auto f = std::async([]{ return 3 + 4; });
    int res = f.get();
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
    int val = f.get();                   // read 端：从 future 中读取结果
    printf("val:%d\n", val);
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

场景三：promise 和 future 都 move 到一个单独 thread 中，promise、future 两者间的通信发生在两个线程间。

[代码](code/promise-future-div-prod.cpp)

### shared_future

promise 和 future 是 1:1 的关系；每个 future 只能调用一次 get()。但可用 shared_future，它可多次调用 get()，每次都得到同样的结果。

较简单的示例：[代码](code/shared-future-demo2.cpp)

较复杂的例子：[代码](code/shared-future-ex.cpp)

注意，shared_future 可以 copy 构造，而 future 只能 move 构造。

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

- eager evaluation: 任务立即执行
- lazy evaluation (call-by-need): 当 `future.get()` 执行时，任务才执行

系统自己决定，是否在单独的线程中执行 `std::async()`。也可以自己指定。

缺省：`std::async()` 立即执行任务
- 指定 std::launch::async：是 eager 的，立即执行；在新线程中执行。
- 指定 std::launch::deferred：是 lazy 的，不立即执行；在同一线程中执行，相当于串行执行。

<font color=red>那为啥还要提供 deferred 方式呢？直接用 do_work() 取代 f = std::async(do_work); f.get(); 不好吗？</font>
一个可能的场景：lazy evaluation。第一个 get 的人，实际执行，后续 get 的人，直接返回结果。要用 shared_future。相当于把结果储存在 future 中。但为何不存在某对象中呢？result_object 呢？

用 std::launch::async 启动
- 若返回的 future 赋给变量：async() 立即返回；但 future.get() 会 block 直到任务结束
- 若返回的 future 没赋给变量（称为 fire-and-forget 模式）：实际上 block 直到任务结束。（具体：asnyc() 返回的 future 会等在其析构函数里，直到相应的 promise 完事。实际上达到了 block 的效果。）

<font color=red>何时用 fire-and-forget 方式？</font>

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
    if (f.valid()) {
        cout << f.get() << endl;
    } else {
        cout << "invalid state" << endl;
    }
```

另一个例子，[代码](code/async-lazy.cpp)
