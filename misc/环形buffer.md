## ring buffer, circular buffer, cyclic buffer, circular queue, circular array

数据读：FIFO 的

## 两个指针的名字

wikipedia
- write_index, end
- read_index, start

[linux kernel api](https://docs.kernel.org/core-api/circular-buffers.html)
- 写：head
- 读：tail

这个 `读 tail ____ head 写` 跟通常习惯相反。

通常，用 array，从左往右，左边是 head，右边是 tail。queue 也是这样。
- array: `读 head   ____ tail 写`。
- queue: `读 front  ____ back 写`
- stack: `无 buttom ____ top 写`

为了避免误解，我们避免用 head、tail，而是用 start、end 比较好。

## mask

环形，start、end 增大、超出范围后，如何得到正确值？

通常思路，用 mod 运算：`start = (start + 1) % capacity`。

若 capacity 是 2 的幂，则可以用位运算：`start = (start + 1) & (capacity - 1)`。这个运算，称为「mask」。下面方法中，用到了 mask 运算，定义如下：

```cpp
    uint32_t mask(uint32_t i) const { return i & (capacity - 1); }
    uint32_t incr(uint32_t &i) const { return (i = mask(i + 1)); }
```

mod 运算要做除法，较昂贵，所以用 mask 更好。但是，因为每次只增 1，所以实际上不需要 mod，只需要 `if (start >= capacity) { start -= capacity; }` 就行，可能也不比 mask 慢。

## 法一，双指针，但为了区分 empty 和 full，只能浪费一个空间

用两个指针 begin, end。无法区分 empty 和 full。为此，只能浪费一个空间。

Typically when the tail pointer is equal to the head pointer, the buffer is empty; and the buffer is full when the head pointer is one less than the tail pointer.

[代码](code/ring-buffer.cpp)

```cpp

```

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

## references
- [I've been writing ring buffers wrong all these years](https://www.snellman.net/blog/archive/2016-12-13-ring-buffers) 及[在 hacker news 上的讨论](https://news.ycombinator.com/item?id=13175832)
- [linux core api: circular buffers](https://docs.kernel.org/core-api/circular-buffers.html)
