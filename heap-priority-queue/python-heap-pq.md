# Python 堆、堆排序

## 堆 heapq

```python
import heapq
li = [5, 7, 9, 1, 3]
heapq.heapify(li)
```
把 list 转成 heap。缺省是 min-heap。现在 li 值为 [1, 3, 9, 7, 5]

```python
heapq.heappush(li, 4)
```
新元素入堆，并自动调整。此时 [1, 3, 4, 7, 5, 9]
 
```python
k = heapq.heappop(li)
```
弹出堆头元素（最小元素），k 为 1。然后 li 自动调整，值为 [3, 5, 4, 7, 9]
若只想访问堆头元素而不弹出它，用 `li[0]`。

```python
heapq.heappushpop(li, item)
```
先将 item 放入堆，再弹出并返回堆顶元素（最小元素）。

```python
heapq.heapreplace(li, item)
```
先弹出并返回堆顶元素（最小元素），再将 item 放入堆。

```python
largest = heapq.nlargest(3, li)
# 相当于 sorted(li, key=key, reverse=True)[:3]
```
得到 li 里最大的三个，逆序，值为 [10, 9, 8]；不改变 li 自身。 

```python
smallest = heapq.nsmallest(3, li)
# 相当于 sorted(li, key=key)[:3]
```
得到 li 里最小的三个，正序，值为 [1, 3, 4]；不改变 li 自身。

## heapq 实现堆排序

```python
def heapsort(iterable):
    h = []
    for value in iterable:
        heappush(h, value)
    return [heappop(h) for i in range(len(h))]

# 或简单一些
def heapsort(iterable):
    h = list(iterable)
    heapq.heapify(h)
    return [heappop(h) for i in range(len(h))]

result = heapsort([1, 3, 5, 7, 9, 2, 4, 6, 8, 0])
# result 结果为 [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

从结果上看，相当于 `sorted(iterable)`，但 `sorted()` 是稳定的，而堆排序是不稳定的。

如何做到稳定？增加一个“顺序”字段，参与比较。

## heapq 如何得到 max-heap

方法一：每个元素都乘以 -1

方法二：未公开的接口（不建议使用）：`_heapify_max()`, `_heappushpop_max()`, `_siftdown_max()`,  `_siftup_max()` 等。

## heapq 自定义比较方式

heapq 不能指定自定义的 comparator。

解决方法一：用 Decorate-Sort-Undecorate (DSU) idiom，用 tuple，把 list 里每个 object 转换成 `(object.排序属性, object.index, object)`，然后排序，最后取出 object。

例：按学生年龄排序。

```python
import heapq

class Student:
    def __init__(self, name, grade, age):
        self.name = name
        self.grade = grade
        self.age = age
    def __repr__(self):
        return repr((self.name, self.grade, self.age))

student_objects = [
    Student('john', 'A', 15),
    Student('jane', 'B', 12),
    Student('dave', 'B', 10),
]

# decorate
d = [(s.grade, i, s) for i, s in enumerate(student_objects)]
heapq.heapify(d)

# 输出
res = [heapq.heappop(d) for i in range(len(d))]

# 另一种输出方式
while d:
    print(heapq.heappop(d))
```

解决方法二：class 自定义 `<` (`__lt__()` 方法)

```python
import heapq

# class Student 定义，student_objects 定义，同上
Student.__lt__ = lambda self, other: self.age < other.age
heapq.heapify(student_objects)
# 下略
```

## 优先级队列 queue.PriorityQueue

主要方法：put(), get(); qsize(), empty(); maxsize(), full()

<font color="red">to add later</font>

```python
from queue import PriorityQueue

customers = PriorityQueue()
customers.put((2, "Harry"))
customers.put((3, "Charles"))
customers.put((1, "Riya"))
customers.put((4, "Stacy"))

# 或 while not customers.empty():
while customers:
    print(customers.get())
```

还有若干用于处理并发的函数。
