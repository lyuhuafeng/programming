# python 排序

内置 list.sort() 和 sorted()。二者都是稳定的。

区别：
* list.sort() 只能用于 list；后者可用于任何 iterable。
* list.sort() 直接改 list 并返回 None；后者返回一个新的 list（不是原来的 iterable 类型！），应该是 key？

## key functions

二者都有一个 key 参数，指定一个 function 或 callable，用在每个 item 上，结果用于比较。

### 用已有的函数作 key。例如 `key=str.lower`

```python
sorted("This is a test string from Andrew".split(), key=str.lower)

# 输出：['a', 'Andrew', 'from', 'is', 'string', 'test', 'This']
```

### 复杂 tuple，通常取其某个字段作比较，`key=lambda student: student[2]`

```python
student_tuples = [
    ('john', 'A', 15),
    ('jane', 'B', 12),
    ('dave', 'B', 10),
]
sorted(student_tuples, key=lambda student: student[2])

# 输出：[('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]
```

### 类对象，取其某个字段作比较，`key=lambda student: student.age`

```python
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
sorted(student_objects, key=lambda student: student.age)   # sort by age

# 输出：[('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]
```

### 用 operator module 的 itemgetter、attrgetter，方便取某个或某些字段

```python
from operator import itemgetter, attrgetter

# tuple, 比较第 2 个字段
sorted(student_tuples, key=itemgetter(2))
# tuple, 先比较第 1 个，再比较第 2 个字段
sorted(student_tuples, key=itemgetter(1,2))
# class object, 比较 age 成员
sorted(student_objects, key=attrgetter('age'))
# class object, 先比较 grade，再比较 age
sorted(student_objects, key=attrgetter('grade', 'age'))
```

### 多次排序：先根据 age 排序，再根据 grade 逆序排序

因为是稳定的，排多次也不会出错。

```python
s = sorted(student_objects, key=attrgetter('age'))
s = sorted(s, key=attrgetter('grade'), reverse=True) 

# 或更进一步，定义如下函数：
def multisort(xs, specs):
    for key, reverse in reversed(specs):
        xs.sort(key=attrgetter(key), reverse=reverse)
    return xs

res = multisort(list(student_objects), (('grade', True), ('age', False)))
```

### key function 里使用外部属性

例如，用于比较的分数存在另外一个 dict 里：

```python
students = ['dave', 'john', 'jane']
newgrades = {'john': 'F', 'jane':'A', 'dave': 'C'}
res = sorted(students, key=newgrades.__getitem__)
```

### comparation function 转成 key function

key vs. comparation
* key function: 返回某 item 的一个绝对值，用于比较。
* comparation function: 返回两个 item 的比较结果（相对位置 relative ordering）。

comparation function `cmp(a, b)` 返回值：
* 负数：表示 less-than
* 0：表示 equal
* 正数：表示 greater-than

使用方法：`key=functools.cmp_to_key(compare_func)`

```python
import functools

def compare_func(a, b):
    return a[0] - b[0]

data = [(8, 'igor'), (7, 'andy'), (5, 'alexy'), (4, 'jerry')]
# res= sorted(data, cmp=compare_func) # python2 用法，python3 中已废弃
res = sorted(data, key=functools.cmp_to_key(compare_func)) # python3 中正确用法
```

## 直接排序：给对象增加 `__lt__()` 方法，使对象可直接比较

list.sort() 和 sorted() 比较两个对象时，使用 `<`。所以，给待排序的类增加 `__lt__()` 方法，就可直接比较，不用指定 key function。

```python
Student.__lt__ = lambda self, other: self.age < other.age

res = sorted(student_objects)
```

若 `__lt__()` 没定义，则使用 `__gt__()`。<font color="red">to add later</font>

## 直接排序：Decorate-Sort-Undecorate (DSU) idiom

又称作 Schwartzian transform。

步骤：
1. 给原 list 增加用于控制顺序的属性 (the initial list is decorated with new values that control the sort order)，得到一个 tuple list。
2. 排序 (the decorated list is sorted)。tuple 是根据其第一个字段排序的。
3. 去掉排序属性，得到排好序的 list (the decorations are removed).

```python
# 为同时得到 index 和 student，需使用 enumerate()。
# 若只想得到 student，无需 enumerate()。
d = [(s.grade, i, s) for i, s in enumerate(student_objects)]
d.sort()
res = [s for grade, i, s in d]
# 或
res = [i[2] for i in d]
```

先比较 grade，再比较序号。序号的作用：
* grade 相同时，本来排在前面的胜出，保持了稳定性。
* grade 相同时，继续比较后面的字段。有序号，确保一定能得到比较结果。若无序号，将继续比较 student 对象。若未定义 `__lt__()`，将得到 `TypeError: '<' not supported between instances of 'Student' and 'Student'` 错误。（但若定义了 `__lt__()`，则可直接排序，无需 DSU）

