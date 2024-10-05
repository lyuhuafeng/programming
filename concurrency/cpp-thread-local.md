# thread-local data

又叫 thread-local storage

在所有线程之外声明，但给每个线程都创建一个。

bound for the thread’s lifetime；在首次使用（first usage）时创建。意味着：
- namespace scope 的，在 first use 之前创建
- 作为 static class member 的，在 first use 之前创建
- 在函数中声明的：在 first use 时创建

<font color=red>usage 和 use 有何区别</font>

注意，main 主线程也是线程，也有一份拷贝！

[例子](code/cpp-thread-local.cpp)


static vs. thread-local vs. local
- static: 与 main thread 的生命周期绑定
- thread_local: 与该 thread 的生命周期绑定
- local: 
