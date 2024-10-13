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

在多线程环境下，在 `contains()` 和 `get()` 之间，key 可能被其他线程删掉，导致出错。（这俩是 thread-safe 的，但这个场景是克服不了的。）若不允许 null key，则不需要该场景，直接 `get()` 即可，不会出错。（当然 java 8 之后可以用 Optional 或 `getOrDefault()` 了）

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

