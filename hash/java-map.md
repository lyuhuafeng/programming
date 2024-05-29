
java.util.Map

# 综述

## 无序的

HashMap
- 最常用
- 允许 null key
- 线程不安全：不支持线程同步，多个线程同时读写，可能引发数据不一致
- 数组+链表/红黑树：每个 bucket 下是个链表或红黑树。若链表长度为8，转换到红黑树；红黑树高度为6，转换到链表。

LinkedHashMap
- 继承自 HashMap
- 新增一个双向循环链表，记录元素的顺序
- 支持两种元素的顺序
  - 插入顺序 insertion-order。默认。遍历时，按当初插入时的顺序返回
  - 访问顺序 access-order。遍历时，按访问顺序，刚访问过的后返回。LRU cache 实现可用此特性。

ConcurrentHashMap (1.7)
- key, value 均不能为 null
- 读写：线程安全；其他操作：自己解锁保证安全
- vs. HashTable: HashTable将每个方法都进行了synchronized同步，ConcurrentHashMap使用了分段锁，将整个Map分成了若干个Segment。

HashTable
- vs. HashMap: 不允许 null key
- vs. HashMap: 线程安全，每个方法都用 synchronized 同步
- 普通的「数组+链表」结构

## 排序的 sorted

- TreeMap 红黑树：不是 thread safe 的

- ConcurrentSkipListMap 跳表

## misc

ThreadLocalMap
- 数组、open addressing。碰撞后，往后 +1。

WeakReferenceHashMap
- 弱引用HashMap。如果WeakReferenceHashMap里的对象仅有WeakReferenceHashMap引用的话，那么在下一次的垃圾回收时，它就会被gc回收掉。
- 使用WeakReferenceHashMap主要是为了防止OOM。

## 特殊目的的

- EnumMap
- WeakHashMap
- IdentityHashMap

## concurrent 的

ConcurrentHashMap

# 线程安全的

## HashTable

出现很早，主要卖点就是 thread safety。

通过 method-level synchronization，给每个方法加 synchronized。put(), putIfAbsent(), get(), remove()。即使读操作也不能并发。

它的 iterator 是 fail-fast 的；若 iterator 创建后，hashtable 的内容有变化，则 iterator 抛出 ConcurrentModificationException。（用 iterator.remove() 是可以的，用 hashtable.remove() 会导致异常）

## ConcurrentHashMap

出现较晚

允许 concurrent reads，允许 limited concurrent writes。允许同时读、有限同时写，而不用把整个对象上锁。性能更好。

它的 iterator 是 weakly consistent 的，不能完全做到 fail-safe。遍历时，实际上是在对象的一个 clone 上操作；即使遍历过程中对象内容有了改变，也不影响正在进行的遍历。坏处：改变的内容可能不会立刻看到。

对比：
- fail-fast: 系统出错时，尽快暴露错误、终止整个操作。
- fail-safe: 系统出错时，尽量避免暴露错误，不终止操作。

内部实现：ConcurrentHashMap 1.7 普通「数组+链表」+分段锁，把整个 map 分为若干个 segment（每个 segment 包括若干 bucket），lock 是在 segment 级别上。所以能允许 limited concurrent writes。

1.8 重写，类似 HashMap 的「数组+链表/红黑树」，但 segment 锁改为 CAS (compare and swap)。lock 是在 bucket 级别上。https://blog.csdn.net/dhaibo1986/article/details/108387790

java 并发编程的两大基石：CAS (compare and swap) 和 AQS。https://www.cnblogs.com/54chensongxia/p/12160085.html

# misc

HashMap作为编程的首选项，速度最快；
LinkedHashMap 取“键值对”的顺序是其插入的顺序，速度比HashMap慢一点，但是遍历迭代的速度更快；
ConcurrentHashMap 线程安全的Map；

TreeMap 基于红黑树的实现，所得到的结果可以经过自定义的排序类进行排序，含有获取子树的方法；

# 各种 set

三种通用的。都是封装了对应的 map 类型。
- HashSet
- TreeSet
- LinkedHashSet

两种特殊用途的
- EnumSet：内部是个 bit-vector，通常是个 long。
- CopyOnWriteArraySet：内部是个 copy-on-write array

EnumSet是一个枚举类的集合类，集合内的所有元素都必须是指定枚举类型的枚举值，枚举类型在创建EnumSet时显式或者隐式地指定；

EnumSet也是有顺序的，该顺序是由枚举值在Enum类中的定义顺序决定。

EnumSet不允许加入null元素，若尝试添加null元素，会抛出NullPointerException异常。

not thread safe
