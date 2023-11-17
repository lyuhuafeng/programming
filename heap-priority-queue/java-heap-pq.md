# Java Priority Queue

```java
java.util.PriorityQueue

public class PriorityQueue<E> extends AbstractQueue<E> implements Serializable
```

offer, poll, remove, add 都是 O(logn)

不是thread-safe。多线程环境下，应使用 `PriorityBlockingQueue`。

## 缺省：min

Java priority queue 缺省是 min priority queue，队头（堆顶）最小，跟 C++ 相反！

## 各种构造函数

```java
PriorityQueue<E>();
PriorityQueue<E>(int initialCapacity);
PriorityQueue<E>(Collection<E> c);
PriorityQueue(PriorityQueue<E> c);
PriorityQueue<E>(SortedSet<E> c);
PriorityQueue<E>(Comparator<E> c);
PriorityQueue(int initialCapacity, Comparator<E> comparator);
```

## 主要操作

```java
PriorityQueue<Integer> pQueue = new PriorityQueue<Integer>();

// 入队：两种
pQueue.add(10); // 若容量不够而不能入队，抛出 IllegalStateException
pQueue.offer(20); // 若容量不够而不能入队，返回 false

// 取堆顶(heap top)或队头(queue head)值，或出队：两种
int p = pQueue.peek(); // 只取值，不弹出。若空，返回null。
int b = pQueue.poll(); // 既取值，又弹出。若空，返回null。

// 为何提供这个奇怪的方法
boolean b = pQueue.remove(8); // 删除某指定值。若值不存在或队已空，返回false。
```

## 遍历

```java
PriorityQueue<Integer> q = new PriorityQueue<>();
int[] nums = {14, 8, 6, 4, 2, 10, 12};
for (int i : nums) {
    q.add(i);
}

System.out.println(q);
System.out.print(q.toArray());
// 两种方法，都输出：[2, 4, 8, 14, 6, 10, 12]。是内部数组的存储顺序。

Iterator it = q.iterator();
while (it.hasNext()) {
    System.out.print(it.next() + " ");
}
System.out.printf("%n");
// 输出：2 4 8 14 6 10 12。是内部数组的存储顺序。

while (!q.isEmpty()) {
    int i = q.poll();
    System.out.printf("%d ", i);
}
System.out.printf("%n");
// 输出：2 4 6 8 10 12 14。正确的从小到大的顺序。
```

## 比较
用 lambda 做 comparator。用 Integer.compare()，导致 min priority queue，就是缺省效果。
```java
PriorityQueue<Integer> q = new PriorityQueue<>(
    (Integer c1, Integer c2) -> Integer.compare(c1, c2)
);
int[] nums = {14, 8, 6, 4, 2, 10, 12};
for (int i : nums) {
    q.add(i);
}
```

用 Collections.reverseOrder() 做 comparator，逆序，得到 max priority queue。可以用于多种数据类型。

```java
PriorityQueue<Integer> q = new PriorityQueue<>(Collections.reverseOrder());
PriorityQueue<String> q = new PriorityQueue<>(Collections.reverseOrder());
```

自定义 comparator。完整代码：[StringCmp.java](code/StringCmp.java)

```java
Comparator<String> customComparator = new Comparator<String>() {
    @Override
    public int compare(String s1, String s2) {
        return s1.length() - s2.length();
    }
};
PriorityQueue<String> q = new PriorityQueue<>(customComparator);
```


自定义 comparator。跟上一个本质上一样。

```java
PriorityQueue<Integer> q = new PriorityQueue<Integer>(new Comparator<Integer>() {
    public int compare(Integer lhs, Integer rhs) {
        if (lhs < rhs) return 1;
        if (lhs.equals(rhs)) return 0;
        return -1;
    }
});
```

若某类实现了 `comparable` interface（主要是重载 `int compareTo()` 方法），则创建 pq 时可用无参的构造函数，不用提供 comparator。

完整代码：[MyOrderDemo.java](code/MyOrderDemo.java)

```java
class MyOrder implements Comparable<MyOrder> {
    // members, constructors, getters, setters

    @Override
    public int compareTo(MyOrder o) {
        return o.orderId > this.orderId ? 1 : -1;
    }
}

PriorityQueue<MyOrder> q = new PriorityQueue<MyOrder>();
```


