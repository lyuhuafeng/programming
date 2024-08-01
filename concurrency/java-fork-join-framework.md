


分治任务模型

两个阶段：任务分解（fork）、结果合并（join）

任务 vs. 分解后的子任务：算法是相似、相同的，但数据规模是不同的。往往用递归算法。

两部分
- 线程池 ForkJoinPool、任务 ForkJoinTask
- 两者的关系，类似 ThreadPoolExecutor 和 Callable

ForkJoinTask: 抽象类
- 两个子类：RecursiveAction（无返回值）、RecursiveTask（有返回值）。都是抽象类。
- 核心方法：fork()、join()、compute()

ForkJoinPool
- 继承自 ExectutorService
- pool 中的每个 thread 都有自己的一个 deque，用于存放 task。用 work-stealing 算法，在不同 thread 间均衡分配 task。
- 启动任务：与 ExecutorService 一样，用 invoke()、submit()、invokeAny()、invokeAll() 方法

例：递归计算 fibonaci 数列，[代码](code/fork_join_fibonaci_demo.java)



One key difference is that F-J seems to be designed to work on a single Java VM, while M-R is explicitly designed to work on a large cluster of machines. These are very different scenarios.

F-J offers facilities to partition a task into several subtasks, in a recursive-looking fashion; more tiers, possibility of 'inter-fork' communication at this stage, much more traditional programming. Does not extend (at least in the paper) beyond a single machine. Great for taking advantage of your eight-core.

M-R only does one big split, with the mapped splits not talking between each other at all, and then reduces everything together. A single tier, no inter-split communication until reduce, and massively scalable. Great for taking advantage of your share of the cloud.


ref:
- https://javabetter.cn/thread/fork-join.html
- https://www.baeldung.com/java-fork-join