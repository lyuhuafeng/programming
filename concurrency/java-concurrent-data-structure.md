# 综述

分类
- thread-unsafe collections
- thread-safe collections
  - synchronized collections
  - concurrent collections

## thread-unsafe collections

在 java.util 中：List, Set, Map; ArrayList, TreeSet, HashMap 等。

遍历（iteration）时返回 fail-fast iterators。
- 遍历过程中，若 collection 被修改，会抛出 concurrent modification exception。

## synchronized collections

普通 collections，通过 java.util.Collections 中的静态 synchronized wrapper 方法，使其 thread-safe。

这些 wrapper 覆盖：Collection, List, Map, SortedMap, Set, SortedSet。

```java
    Collection<Integer> sc = Collections.synchronizedCollection(new ArrayList<>());
    List<Integer> sl = Collections.synchronizedList(new ArrayList<>());
    Map<Integer, String> sm = Collections.synchronizedMap(new HashMap<>());
    Map<Integer, String> ssm = Collections.synchronizedSortedMap(new TreeMap<>());
    Set<Integer> ss = Collections.synchronizedSet(new HashSet<>());
    SortedSet<Integer> sss = Collections.synchronizedSortedSet(new TreeSet<>());
```

只是保护每个方法。即，某个方法执行时，其他线程无法修改 collection。

但遍历时还是要自己保护一下。因为「遍历」包含多次操作，需要搞成 atomic 的。

```java
    List<String> sc = Collections.synchronizedList(Arrays.asList("a", "b", "c"));
    List<String> uc = new ArrayList<>();
    Runnable listOperations = () -> {
        synchronized (sc) {
            sc.forEach((e) -> {
                uc.add(e.toUpperCase());
            });
        }
    };
```

## concurrent collections

真正原生支持 concurrency 的容器。

在 java.util.concurrent 中：
- BlockingQueue: ArrayBlockingQueue, DelayQueue, LinkedBlockingQueue, PriorityBlockingQueue, SynchronousQueue; LinkedBlockingDeque, LinkedTransferQueue
- ConcurrentMap: ConcurrentHashMap, ConcurrentNavigableMap, ConcurrentSkipListMap

遍历（iteration）时返回 weakly-consistent iterators。「返回某元素」，即「returned by iterator」，其实就是指「遍历到了该元素」。
- 遍历开始后，若某元素被删，但还没被 `it.next()` 返回，则它以后也不会被返回。
- 遍历开始后，新增的元素，可能会被返回，也可能不会返回。
- 遍历过程中，不会有元素被返回超过一次。

synchronized collections vs. concurrent collections
- synchronized: 通过 intrinsic lock 实现。每个方法都用 synchronized 关键字做同步，把整个 collection 锁住。性能不好。
- concurrent: 把数据分成 segments，不同线程分别锁不同的 segment。性能好。

# ConcurrentMap

提供了不可分的操作：`putIfAbsent()`, `remove()`, `replace()`

不需要先判断是否存在，再 put/remove/replace。

若简单分成两步，是无法做到原子化的。

解法：把 check 和 put 一起保护起来。但代价太大：把整个 map 都锁了。

```java
    synchronized(map) {
        if (!map.containsKey(key)) {
            map.put(key, val);
        }
    }
```

ConcurrentHashMap 的 value 不能是 null。否则会破坏 thread-safe。具体见下。

TreeMap 没有 concurrent 版本。恐怕是因为让一个 tree 结构支持并发代价太大了。

# Hashtable vs. HashMap vs. ConcurrentHashMap

Hashtable

- thread-safe：所有方法都用 synchronized 关键字做同步
- 不允许 null key/value；试图插入 null 键或值，会抛出 NullPointerException。
- 哈希冲突解决：使用链表法解决哈希冲突。每个桶（bucket）是一个链表，冲突的元素会被添加到链表的末尾。
- 其 keySet() 也是 thread-safe 的。返回一个 KeySet 视图，它是一个同步的集合视图。当你对这个集合进行操作时，会同步到原始的 Hashtable。

HashMap

- not thread-safe，多线程环境下需手动同步
- 允许 null key/value：因为 key 不能重复，所以也只能有一个 null key。null value 可以存在多个。
- 哈希冲突解决：同样使用链表法解决哈希冲突；但在 Java 8 之后，若链表长度超过阈值（默认是8），会转为红黑树，以提高性能。
- 其 keySet() 也不是 thread-safe 的，多线程环境下需要外部同步；返回一个 KeySet 视图，它是非同步的集合视图。如果在多线程环境下使用，需要手动同步。


ConcurrentHashMap
- 进化成 thread-safe
- （与 Hashtable 一样）不允许 null key/value。

# 为何 thread-safe 的两个，都不允许 null key/value？

因为额外支持 null key/value 导致性能下降，而实际上又很少用到。

key 不允许，（一）因为 key object 必须实现 `equals()` 和 `hashCode()` 方法。但 null 不是个对象，无法实现。（二）作者也不想用 key masking（用特殊值代替 null，例如下面的 NULL_OBJECT）这种方式。

```java
    private static final Object NULL_OBJECT = new Object();

    // for put
    if (value == null) {
        value = NULL_OBJECT;
    }

    // for get
    return (value == NULL_OBJECT) ? : null : value;
```

value 不允许，作者自己的解释：

The main reason that nulls aren't allowed in ConcurrentMaps (ConcurrentHashMaps, ConcurrentSkipListMaps) is that ambiguities that may be just barely tolerable in non-concurrent maps can't be accommodated. The main one is that if map.get(key) returns null, you can't detect whether the key explicitly maps to null vs the key isn't mapped. In a non-concurrent map, you can check this via map.contains(key), but in a concurrent one, the map might have changed between calls.

也就是：若 `get()` 返回 null，无法区分是 key 不存在，还是 key 存在但 value 为 null。为了区分，则要先判断再 `get()`，如下：

```java
    if (map.contains(key)) {
        return map.get(key);
    } else {
        throw new KeyNotFoundException;
    }
```

在多线程环境下，在 `contains()` 和 `get()` 之间，key 可能被其他线程删掉，导致出错。（这俩分别是 thread-safe 的，但它俩作为两个步骤合在一起就不是了。）若不允许 null key，则不需要该场景，直接 `get()` 即可，不会出错。（当然 java 8 之后可以用 Optional 或 `getOrDefault()` 了）

通用原则：任何 Collections 都不应该允许 null 成员。null 在 api 里应该用来指示出错（如 key 不存在）。

# TreeMap

TreeMap allows null key if a defined comparator allows it: in case of natural ordering, accessing or putting with null key results in NullPointerException. Following example shows null allowing comparator:

```java
    Comparator<Integer> myCmp = Comparator.nullsFirst(Comparator.naturalOrder());
    NavigableMap<Integer, String> m =  new TreeMap<>(myCmp);
    m.put(null, "Unpleasant Null");
    m.put(50, "This is 50");
    m.put(20, "this is 20");
    System.out.println(m);
```

TreeMap 不是 thread-safe 的！也没有对应的 thread-safe ConcurrentTreeMap！恐怕是因为让一个 tree 结构支持并发代价太大了。想得到 thread-safe 的、支持 concurrent 的、有序的 collection，用 ConcurrentSkipListMap（或 Set）。

# Null as key In EnumMap

EnumMap strictly requires keys to be a defined enum type, hence it doesn’t allow null as key. EnumMap has effective use cases and allowing null as key would not serve any purpose anyway.

