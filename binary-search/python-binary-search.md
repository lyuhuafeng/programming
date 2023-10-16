# python 二分搜索

```python
import bisect

pos = bisect.bisect_left(list, num, beg, end)
# 返回最左边的可插入位置，也就是第一个大于等于num的位置。
# 相当于C++ std::lower_bound()。

pos = bisect.bisect_right(list, num, beg, end)
pos = bisect.bisect(list, num, beg, end)
# 返回最右边的可插入位置，也就是第一个大于num的位置。
# 相当于 C++ std::upper_bound()。
```

原 `list` 是有序的。返回结果 `pos`，如果在 `pos` 位置插入 `num`，则 `list` 仍然是有序的。

如果 `num` 不在 `list` 中，两者返回值相同，都是可插入位置。

如果 `num` 在 `list` 中出现一次，`left` 者返回 `num` 的下标，`right` 者返回 `'num 下标 + 1'`。

如果 `num` 在 `list` 中出现多次，`left` 者返回最左边的下标，`right` 者返回 `'最右边的下标 + 1'`。

```python
import bisect
list1 = [1, 3, 5, 8, 12]
pos = bisect.bisect_right(list1, 7)
# pos值为3
list1.insert(pos, 7)
# list1现在为：[1, 3, 5, 7, 8, 12]
```

这三个则是直接插入，不用先查找再插入
```python
import bisect

insort_left(list, num, beg, end)
insort_right(list, num, beg, end)
insort(list, num, beg, end)
```

附录：`list` 插入操作

```python
list1 = [1, 2, 3, 4, 5, 6, 7]
# insert 10 at 4th index
list1.insert(4, 10)
# 结果：[1, 2, 3, 4, 10, 5, 6, 7]。
# 原先list[4] = 5，现在被新插入者挤到后面了。
```
