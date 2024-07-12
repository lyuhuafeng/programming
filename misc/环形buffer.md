## ring buffer, circular buffer, cyclic buffer, circular queue, circular array

数据读：FIFO 的

## 两个指针的名字

wikipedia
- 写：write_index, end
- 读：read_index, start

[linux kernel api](https://docs.kernel.org/core-api/circular-buffers.html)
- 写：head
- 读：tail

这个 `读 tail ____ head 写` 跟通常习惯相反。

通常，用 array，从左往右，左边是 head，右边是 tail。queue 也是这样。
- array: `读 head   ____ tail 写`
- queue: `读 front  ____ back 写`
- stack: `读 buttom ____ top  写`

为了避免误解，避免用 head、tail，而是用 start、end 比较好。

## 判断 empty、full

按惯例，`[start, end)` 左闭右开区间。`end` 位置是不占用的。

初始，为空，满足 `start == end`。

当 end 从后面追上 start，满。此时 `end == start`。但发现与「空」的条件无法区分。为解决，只能浪费一个空间，`end + 1 == start` 就认为「满」。注意，`end + 1` 实际上应该用 `to_idx(end + 1)`。

## 得到正确的下标

环形，start、end 增大、超出范围后，如何得到正确值？

思路一，用 mod 运算：`start = (start + 1) % capacity`。但 mod 运算要做除法，较贵。

思路二，若 capacity 是 2 的幂，则可以用位运算，比 mod 运算「便宜」：`start = (start + 1) & (capacity - 1)`。这个运算，称为「mask」。下面代码中，`to_idx()` 就用了 mask 位运算：

```cpp
    uint32_t to_idx(uint32_t i) const { return i & (capacity - 1); } // 用了 mask 位运算
    uint32_t incr(uint32_t &i) const { return (i = to_idx(i + 1)); }
```

思路三，但是，因为每次只增 1，所以实际上不需要 mod，只需要 `if (start >= capacity) { start -= capacity; }` 就行，可能也不比 mask 慢，且更易读。代码如下：

```cpp
    int to_idx(int i) { return i >= capacity ? i - capacity : i; }
    int incr(int &i) { return (i = to_idx(i + 1)); }
```    

## 法一，双指针，但为了区分 empty 和 full，只能浪费一个空间

用两个指针 start, end。无法区分 empty 和 full。为此，只能浪费一个空间。

Typically when the tail pointer is equal to the head pointer, the buffer is empty; and the buffer is full when the head pointer is one less than the tail pointer.

用 mask 位运算：[代码](code/ring-buffer.cpp)。若 full 则新数据覆盖旧数据。

用思路三，[leet 622. 循环队列](https://leetcode.cn/problems/design-circular-queue) [代码](code/leet-622-circular-queue.cpp)。若 full 则新数据无法写入。注意，按题意，实际容量 k，则 `capacity = k + 1`。

用思路三，[leet 641. 循环双端队列](https://leetcode.cn/problems/design-circular-deque) [代码](code/leet-641-circular-deque.cpp) 比 622 多了一点逻辑。

## 法二，一个 start 指针，一个 size 变量，不浪费空间

用 begin 记录开始位置，用 size 记录已经写入了多少元素。

cons：在并发环境下，read/write 都要写 size 变量；每次 read 都要读 begin 和 size 并更新它们。

## 法三，双指针，unmasked，不浪费空间

两个指针 start 和 end，但它俩值增加时，不 mask，只有在需要用它俩值访问 buf 时才 mask。它俩的值增大，直到 overflow 再 wrap around 重新从 0 开始。

注意：
- 用 unsigned int 类型，且所用编程语言支持「wraparound on unsigned integer overflow」。c++ 满足此条件。
- capacity 必须为 2 的幂。（why? 没看明白, to check later）
- 最大的 capacity 是 start/end 数据类型的最大值的一半。
- <font color="red">to check later: 两个指针，有一个 wraparound 了，另一个还没有，如何处理？</font>

[代码](code/ring-buffer-unmasked.cpp)

## thread-safe

https://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

https://stackoverflow.com/questions/9743605/thread-safe-implementation-of-circular-buffer

## references
- [I've been writing ring buffers wrong all these years](https://www.snellman.net/blog/archive/2016-12-13-ring-buffers) 及[在 hacker news 上的讨论](https://news.ycombinator.com/item?id=13175832)
- [linux core api: circular buffers](https://docs.kernel.org/core-api/circular-buffers.html)
- [linux: a lockless ring-buffer](https://lwn.net/Articles/340400/)

https://psy-lob-saw.blogspot.com/2014/04/notes-on-concurrent-ring-buffer-queue.html


Looking at the Queue interface guarantees
https://psy-lob-saw.blogspot.com/2014/07/poll-me-maybe.html
