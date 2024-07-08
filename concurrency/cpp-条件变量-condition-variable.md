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



全局变量，或 class 成员变量，或 static 变量。
```cpp
    condition_variable cv;
    mutex mtx;
    bool ready; // 两个线程共享的状态变量
```

producer 里：

注意：

consumer 中，需要（可能多次）对 mutex 执行 lock 和 unlock 操作，所以得用 unique_lock。（lock_guard 做不到）

producer 中，只要 lock 一次，用来保护改写 condition，然后直接释放（销毁）就行，所以用 lock_guard 就行了。lock_guard also doesn't allow access to the mutex itself which most condition variable implementations probably require.

https://stackoverflow.com/questions/13099660/c11-why-does-stdcondition-variable-use-stdunique-lock 这里有关于 condition_variable_any 的讨论

```cpp
{
    ... // do some work
    {   // 在 mtx 的保护下，修改「状态变量」的值
        std::lock_guard<std::mutex> guard(mtx);
        ready = true;
    } // release lock and mutex
    // Trigger thread B to recheck conditions
    cv.notify_one(); // 通知 consumer 线程，去再次检查「状态变量」的值
    ... // continue with some other work
}

consumer 的四种写法。推荐把 predicate 作为参数传给 wait()，也就是写法二、四。

```cpp
{
    ...
    //--- wait until data are prepared ---
    std::unique_lock<std::mutex> ulock(myDataMutex);
    while (!ready) {
        cv.wait(ulock); // waiting 时，自动 unlock，以使 producer 线程可以修改「状态变量」
        // wait 返回后（收到了对方的 notify），自动 relock
        // 此时 locked。在其保护下，可重新检查「状态变量」（就是 while (!ready) 这句）
    }
    // mutex 仍然/还是 处于 locked 状态，可以读写访问「状态变量」
}
```

wait(ulock) 函数会自动释放 ulock（若不释放，producer 线程无法修改「状态变量」），使线程进入 wait 状态，等待 cv 信号；收到信号后，wait() 会自动重新 acquire the mutex 并返回。也就是说，wait 返回后，mtx 是被 locked 的，此时可以检查或写「状态变量」。

consumer 中，法二，check 和 wait 合并

把 check 用到的 predicate 条件（callable 类型），作为参数，传给 wait()。

```cpp
{
    unique_lock<mutex> ulock(mtx);
    cv.wait(ulock, []{ return data_ready; });
}
```

consumer 写法三，增加 wait 最大时长

- wait_until(): 返回值是 std::cv_status::timeout 或 std::cv_status::no_timeout:
- wait_for(): 嵌入式的，返回值是 bool 类型，表示是否超时。

```cpp
    auto timePoint = std::chrono::system_clock::now() + chrono::seconds(5); // 最多等 5 秒钟
    std::unique_lock<std::mutex> uLock(myDataMutex);

    while (!ready) {
        if (cv.wait_until(uLock, timePoint) == std::cv_status::timeout) {
            // 超时了，但「状态变量」还没满足。做一些 error handling
            break;
        } else {
            // 返回值为 cv_status::no_timeout，没超时，且条件满足：正确处理
        }
    }

    // 或
    if (cv.wait_for(uLock, timeoutPeriod, []{ return ready; })) {
        // 没超时，且条件满足：正确处理
    } else {
        // 超时，条件还没满足：error handling
    }
```

不安全的用法：

在 producer 中直接 notify_one() 或 notify_all()，在 consumer 中直接 wait()
```cpp
    // global condition variable, shared by both
    condition_variable cv;
    // in producer
    cv.notify_all();
    // in consumer
    wait(cv);
```

这样简单粗暴的使用，在大多数情况下都是 work 的。但不安全，有两个问题：
- lost wakeup: 若 notify 发生在 wait() 之前，其 signal 不会被 consumer 收到，而 consumer 稍后调用 wait() 就会一直等下去。
- spurious wakeup: 有些库写得有 bug，在没有 notify 的情况下，wait 也会返回。导致不能确定，是否是 thread A 唤醒了我。

所以，不能单独使用 cv。必须有个状态变量（condition），如上面代码中的 ready。
- 简单粗暴：notify() 通知：现在好了
- 正确：notify() 通知：现在可以去检查一下 condition，看是不是好了

既然有了变量 condition，就得用 mutex 来保护它。

所以，最终结论：cv 总是与 condition 和 mutex 一起使用。




生产者 ready 时，通知消费者；消费者一直等，直到被通知。

- consumer: 调用 `wait()`。该函数内部 acquires the mutex 并检查 condition 是否满足。（如果不满足，则 release mutex 并等待被 signaled。此时 consumer 被 blocked。
释放锁并等待 condition variable 信号（线程被阻塞）。condition variable 的 wait() 函数提供这两个操作原子化。）
Thread 1 calls the wait on condition variable, which internally acquires the mutex and check if required condition is met or not.
If not then it releases the lock and waits for Condition Variable to get signaled ( thread gets blocked). Condition Variable’s wait() function provides both these operations in atomic manner.

- producer: 当 condition 满足时，producer 通知（signals the condition varialbe)

- consumer: 当 condition varialbe 被 signal 了，正在等待该 signal 的 consumer 重新开始运行。它重新 acquire mutex 并检查 doncition 是否满足，或者是个 superiors call. 若 superiors，它再次调用 wait.







条件变量是c++11引入的一种同步机制，它可以阻塞一个线程或者个线程，直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁配合使用，这里的锁就是上面介绍的std::unique_lock。

condition_variable（条件变量）是 C++11 中提供的一种多线程同步机制，它允许一个或多个线程等待另一个线程发出通知，以便能够有效地进行线程同步。

condition_variable 需要与 mutex（互斥锁）一起使用。当线程需要等待某个条件变成真时，它会获取一个互斥锁，然后在条件变量上等待，等待期间会自动释放互斥锁。另一个线程在满足条件后会获取相同的互斥锁，并调用条件变量的 notify_one() 或 notify_all() 函数来唤醒等待的线程。
