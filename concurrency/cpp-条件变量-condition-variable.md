## std::condition_variable

https://stackoverflow.com/questions/50331130/please-explain-the-use-of-condition-variables-in-c-threads-and-why-do-we-need

https://thispointer.com/c11-multithreading-part-7-condition-variables-explained/

https://stackoverflow.com/questions/38147825/shared-atomic-variable-is-not-properly-published-if-it-is-not-modified-under-mut


https://leimao.github.io/blog/CPP-Condition-Variable/



Objects of type condition_variable always use unique_lock<mutex> to wait: for an alternative that works with any kind of lockable type, see condition_variable_any



Condition variables allow one to atomically release a held mutex and put the thread to sleep. Then, after being signaled, atomically re-acquire the mutex and wake up. You run into this, for example, in the producer/consumer problem. You will deadlock if you go to sleep while holding the mutex, but you could also deadlock if you release it before sleeping (by missing the signal to wake up).

several well-known pitfalls and caveats to using condition variables

cv 总是与 mutex 同时使用。

The mutex must be held when wait is called. You should always verify that the desired condition is still true after returning from wait. That's why you always see conditional waits wrapped in a while loop. C++11 also gives you the predicate overload, which is syntactic sugar for the while loop.

The mutex protects the shared state. The condition lets you block until signaled.

unique_lock is an RAII (Resource Acquisition Is Initialization) wrapper for locking and unlocking the given mutex. It's conceptually identical to the lock statement in C#. It simplifies exception handling by tying the mutex acquisition and release to the lifetime of the unique_lock instance. I don't know if there's a reason why condition_variable forces you to use it other than the fact that it's good practice. The only difference between unique_lock and lock_guard is that unique_lock can be unlocked... which is why you have to use it instead of lock_guard with condition_variable.


cv 总是与 mutex 同时使用。


全局变量，或 class 成员变量，或 static 变量。
```cpp
    std::condition_variable cv;
    std::mutex mtx;
    bool data_ready; // 两个线程共享的状态变量
```

注意：

consumer 中，需要（可能多次）对 mutex 执行 lock 和 unlock 操作，所以得用 unique_lock。（lock_guard 做不到）

producer 中，只要 lock 一次，用来保护改写 condition，然后直接释放（销毁）就行，所以用 lock_guard 就行了。lock_guard also doesn't allow access to the mutex itself which most condition variable implementations probably require.

lock_guard 和 unique_lock 在创建时，都会设法 lock 住 mutex。如果 mutex 已经处于 locked 状态，则 lock_guard 和 unique_lock 的创建都会 block 住，直到 mutex 被 unlock。所以，注意 mutex 的状态。

wait() 会自动释放 mutex，使线程进入 wait 状态。如果有多个线程都调用 `unique_lock(mutex); wait();`，则一个拿到 mutex 的线程在 wait() 里释放 mutex 后，其他线程得以获得 mutex 并调用 wait() 并自动释放 mutex…… 从而可以实现多个线程都在 wait 状态。

https://stackoverflow.com/questions/13099660/c11-why-does-stdcondition-variable-use-stdunique-lock 这里有关于 condition_variable_any 的讨论

producer 里：

```cpp
{
    ... // 干活
    {   // 活干完，在 mtx 的保护下，修改「状态变量」data_ready 的值
        std::lock_guard<std::mutex> guard(mtx); // 若 mtx 已经是 locked 状态，则此处创建 lock_guard 会 block 住
        data_ready = true;
    } // release lock and mutex
    cv.notify_one(); // 通知 consumer 线程，去再次检查「状态变量」的值
    ... // continue with some other work
}

consumer 的四种写法。推荐把 predicate 作为参数传给 wait()，也就是写法二、四。

写法一。注意，先检查 data_ready 再 wait()；若 wait() 之前 data_ready 就已经是 true，则不用 wait() 也不用等被 notify 就继续了。
```cpp
{
    ...
    //--- wait until data are prepared ---
    std::unique_lock<std::mutex> ulock(mtx); // 若 mtx 已经是 blocked 状态，则此处创建 uniqu_lock 会 block 住
    // 此时，mtx 处于 locked 状态
    while (!data_ready) {
        cv.wait(ulock); // waiting 时，自动 unlock，以使 producer 线程可以修改「状态变量」
        // wait 返回后（收到了对方的 notify），自动 relock
        // 此时 locked。在其保护下，可重新检查「状态变量」（就是 while (!ready) 这句）
    }
    // 此时，从 cv.wait() 返回后，mutex 又 处于 locked 状态，可以读写访问「状态变量」
}
```

consumer 中的 `cv.wait(ulock)` 函数会自动释放 ulock（若不释放，producer 线程无法修改「状态变量」），使线程进入 wait 状态，等待 cv 信号；consumer 收到信号后，`cv.wait()` 会自动重新 acquire mutex 并返回。也就是说，wait 返回后，mtx 是 locked 状态，此时可以检查或写「状态变量」。

注意，即使 data_ready 是 atomic 类型的，也需要用 mutex 来保护它。为何？如下所示，如无 mutex 保护，则可能：(1) data_ready == false; (2) producer 在这个 time window 里改了 data_ready 并发了 notification，但此时我这边还没进入 wait 状态，没收到该 notification; (3) 一直 wait 下去。

```cpp
    //--- 若 data_ready 没有用 mutex 来保护 ---
    std::unique_lock<std::mutex> ulock(mtx);
    while (!data_ready.load()) { // (1) 此时 data_ready == false，从而进入循环体
        do_work(); // (2) a time window，对方在这个 time window 里改了 data_ready 并发了通知（但我没收到）
        cv.wait(ulock); // (3) 收不到通知，一直 wait 下去
    }
```

所以，mutex 保护的是 check-wait 这个整体。若有了 mutex 保护，则有两种可能的执行顺序，都是正确的：
- (1) consumer 先拿到锁，进入 wait 状态并释放锁；producer 拿到锁，改了 data_ready 并发通知；consumer 从 wait 中醒来，在 while 处检查成功，退出 while 循环，进入后续流程。
- 或者 (2) producer 先拿到锁，干活，改 data_ready 并发通知；consumer 在 producer 改完 data_ready（并自动释放锁）之后，拿到锁，在 while 处检查成功，不用 wait 就继续了，对方发的通知被忽略但没关系。

<font color=red>吕注：其实 mutex 除了保护这个 data_ready，还保护了真正的写数据。为啥书上好像都没提这事？</font>

consumer 中，法二，check 和 wait 合并

把 check 用到的 predicate 条件（callable 类型），作为参数，传给 wait()。

注意，这个版本的 `wait()`，相当于 `while (!data_ready) { cv.wait(ulock); }`，所以，类似地，若调用 `wait()` 时 data_ready 已经是 true，则不用等到被 notify 就返回了。

```cpp
{
    unique_lock<mutex> ulock(mtx); // 若 mtx 已经是 blocked 状态，则此处创建 uniqu_lock 会 block 住
    // 此时，mtx 处于 locked 状态
    cv.wait(ulock, []{ return data_ready; }); // waiting 时，自动 unlock，以使 producer 线程可以修改「状态变量」
    // 从 cv.wait() 返回后，mutex 又处于 locked 状态，可以读写访问「状态变量」
}
```

consumer 写法三，增加 wait 最大时长

- `wait_until()`: 返回值是 `std::cv_status::timeout` 或 `std::cv_status::no_timeout`
- `wait_for()`: 嵌入式的，返回值是 bool 类型，表示是否超时。

```cpp
    auto timePoint = std::chrono::system_clock::now() + chrono::seconds(5); // 最多等 5 秒钟
    std::unique_lock<std::mutex> ulock(mtx);

    while (!data_ready) {
        if (cv.wait_until(ulock, timePoint) == std::cv_status::no_timeout) {
            // 没超时，且条件满足：正确处理
        } else {
            // 返回值为 cv_status::no_timeout，超时了，但「状态变量」还没满足。
            // 做一些 error handling
            break;
        }
    }

    // 或
    if (cv.wait_for(ulock, timeoutPeriod, []{ return data_ready; })) {
        // 没超时，且条件满足：正确处理
    } else {
        // 超时，条件还没满足：error handling
    }
```

不安全的用法：

没有「状态变量」（也就不需要 lock/mutex 来保护对该「状态变量」的访问）。在 producer 中直接 `notify_one()` 或 `notify_all()`，在 consumer 中直接 `wait()`。

```cpp
    // global condition variable, shared by both
    std::condition_variable cv;
    // in producer
    cv.notify_all();
    // in consumer
    cv.wait(); // 没有 lock 的存在
```

这样简单粗暴的使用，在大多数情况下都是 work 的。但不安全，有两个问题：
- lost wakeup: 若 notify 发生在 `wait()` 之前，其 signal 不会被 consumer 收到，而 consumer 稍后调用 `wait()` 就会一直等下去。
- spurious wakeup: 有些库写得有 bug，在没有 notify 的情况下，wait 也会返回。导致不能确定，是否是 thread A 唤醒了我。

所以，不能单独使用 cv。必须有个状态变量（condition），如上面代码中的 data_ready。
- 简单粗暴：`notify()` 通知：现在好了
- 正确：`notify()` 通知：现在可以去检查一下 condition，看是不是好了

既然有了变量 condition，就得用 mutex 来保护它。

所以，最终结论：cv 总是与 condition 和 mutex 一起使用。




生产者 ready 时，通知消费者；消费者一直等，直到被通知。

- consumer: 调用 `wait()`。该函数内部 acquires the mutex 并检查 condition 是否满足。（如果不满足，则 release mutex 并等待被 signaled。此时 consumer 被 blocked。
释放锁并等待 condition variable 信号（线程被阻塞）。condition variable 的 wait() 函数提供这两个操作原子化。）
Thread 1 calls the wait on condition variable, which internally acquires the mutex and check if required condition is met or not.
If not then it releases the lock and waits for Condition Variable to get signaled ( thread gets blocked). Condition Variable’s wait() function provides both these operations in atomic manner.

- producer: 当 condition 满足时，producer 通知（signals the condition varialbe）

- consumer: 当 condition varialbe 被 signal 了，正在等待该 signal 的 consumer 重新开始运行。它重新 acquire mutex 并检查 doncition 是否满足，或者是个 superiors call. 若 superiors，它再次调用 wait.
