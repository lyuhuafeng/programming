# Python 堆、堆排序

# 堆

```python
import heapq
li = [5, 7, 9, 1, 3]
heapq.heapify(li)
```
把list转成heap。缺省是min-heap。现在li值为[1, 3, 9, 7, 5]

```python
heapq.heappush(li, 4)
```
新元素入堆，并自动调整。此时 [1, 3, 4, 7, 5, 9]
 
```python
k = heapq.heappop(li)
```
弹出堆头元素（最小元素），k 为 1。然后 li 自动调整，值为 [3, 5, 4, 7, 9]
若只想访问堆头元素而不弹出它，用 li[0]。

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

## 堆排序

```python
def heapsort(iterable):
    h = []
    for value in iterable:
        heappush(h, value)
    return [heappop(h) for i in range(len(h))]

result = heapsort([1, 3, 5, 7, 9, 2, 4, 6, 8, 0])
# result 结果为 [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

从结果上看，相当于 `sorted(iterable)`，但 `sorted()`是稳定的，而堆排序是不稳定的。

如何做到稳定？增加一个”顺序“字段，参与比较。

## 如何得到 max-heap

方法一：每个元素都乘以 -1

方法二：未公开的接口（不建议使用）：`_heapify_max()`, `_heappushpop_max()`, `_siftdown_max()`,  `_siftup_max()` 等。

## 优先级队列

```python
from queue import PriorityQueue

customers = PriorityQueue()
customers.put((2, "Harry"))
customers.put((3, "Charles"))
customers.put((1, "Riya"))
customers.put((4, "Stacy"))

while customers:
    print(customers.get())
```

还有若干用于处理并发的函数。
