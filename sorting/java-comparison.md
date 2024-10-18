# 何时需要比较

* 对类对象排序。`Collections.sort()`, `Arrays.sort()`。
* 对 `Map` 的 key 或 value 排序。`TreeMap` 构造函数，或 `Collections.sort()` 方法。
* `PriorityQueue` 的构造函数。
* 用 Stream API 对流中元素排序。`sorted()` 方法。

# 比较的结果（返回值）

两个对象 o1、o2 比较，返回值：

* `< 0` : o1 < o2
* `= 0` : o1 == o2
* `> 0` : o1 > o2

「小于」，返回负值即可，不用必须是 -1。「大于」，类似。

## 避免使用 subtraction trick

因为不用返回 -1, 0, +1，所以一个常见 trick 是，直接返回二值相减的结果。此法逻辑上正确，但减法结果可能超出数据范围，故应避免此法。

```java
// 逻辑正确，但应避免
    Comparator<Player> comparator = (p1, p2) -> p1.getRank() - p2.getRank();
```

# Comparable interface vs. Comparator interface

Java 不支持操作符重载，不能像 C++ 那样，定义单独的 `bool operator<(const T a, const T b)` 做比较。

Comparable 和 Comparator 二者，首选 Comparable。定义了 natural ordering。不用额外参数。

何时使用 comparator？
* 无法修改被比较的类的代码，无法为其 implements Comparable
* 除了 natural ordering，还需要其他比较方式

二者分别重载 `compareTo()` 和 `compare()` 方法。

如何记忆？从英文含义看，
* "compare to sth" 表示「与 sth 比较」，可见应该只有一个参数，所以属于 Comparable；
* "compare a and b" 表示「比较 a、b 二者」，自然有两个参数，所以属于 Comparator。

```java
    class T implements Comparable<T> {
        @Override
        public int compareTo(T other) { ... } // 比较 this 和 other 两者
    }

    class MyComparator implements Comparator<T> {
        @Override
        public int compare(T o1, T o2) { ... } // 比较 o1 和 o2 两者
    }
```

Comparable 例子。完整例子代码：[MyOrderDemo.java](code/MyOrderDemo.java)

```java
    public class Player implements Comparable<Player> {
        // members, constructors, getters, setters...
        @Override
        public int compareTo(Player otherPlayer) {
            return Integer.compare(getRanking(), otherPlayer.getRanking());
        }
    }

    // sort() 不需要 comparator 参数
    Collections.sort(footballTeam);
```

Comparator 例子

```java
    public class ByRanking implements Comparator<Player> {
        @Override
        public int compare(Player p1, Player p2) {
        return Integer.compare(p1.getRanking(), p2.getRanking());
        }
    }

    // ByRanking 对象作为 sort() 的第二个参数
    Collections.sort(footballTeam, new ByRanking());
```

# Comparator

1. 基本 sort，不使用 lambda。 

可以在 `sort()` 参数中直接定义 comparator 对象，也可以先定义好 comparator 对象，再在 `sort()` 中引用。代码：[CmpDemo.java](code/CmpDemo.java)。

```java
    // 1. basic sorting, 未使用 lambda
    // 在 sort() 参数中直接定义 comparator 对象
    Collections.sort(humans, new Comparator<Human>() {
        @Override
        public int compare(Human h1, Human h2) {
            return h1.getName().compareTo(h2.getName());
        }
    });

    // 1.a. basic sorting, 未使用 lambda
    // 先定义好 comparator 对象（注意其类型是 Comparator<T>），再在 sort() 中引用
    Comparator<Human> cmpByAge = new Comparator<>() {
        @Override
        public int compare(Human h1, Human h2) {
            return h1.getAge() <= h2.getAge() ? -1 : 1;
        }
    };

    Collections.sort(humans, cmpByAge);
```

2. 用 lambda

其参数可以带类型，也可以不带类型。代码：[CmpDemo.java](code/CmpDemo.java)。

```java
    // lambda 参数带类型
    humans.sort((Human h1, Human h2) -> h1.getName().compareTo(h2.getName()));

    // lambda 参数不带类型
    humans.sort((h1, h2) -> h1.getAge() <= h2.getAge() ? -1 : 1);

    // lambda 当做变量。注意其类型是 Comparator<T>
    Comparator<Human> byAge = ((h1, h2) -> h1.getAge() <= h2.getAge() ? -1 : 1);
    humans.sort(byAge);
```

3. lambda 中引用一个 static method

在带比较的类中定义 static 的比较函数。`sort()` 参数中引用。代码：[CmpDemo2.java](code/CmpDemo2.java)。

```java
    class Human {
        // ...
        public static int byNameThenAge(Human h1, Human h2) {
            if (h1.name.equals(h2.name)) {
                return Integer.compare(h1.age, h2.age);
            } else {
                return h1.name.compareTo(h2.name);
            }
        }
    }

    humans.sort(Human::byNameThenAge);
```

该 static method 也可以不定义在待比较的类中。此时该方法中需使用 getters 访问对象中成员。代码：[CmpDemo3.java](code/CmpDemo3.java)。

```java
    class CmpDemo3 {
        // 在 Human 类之外定义 static 比较函数。用 getter 访问 Human 对象中成员
        public static int byNameThenAge(Human h1, Human h2) {
            if (h1.getName().equals(h2.getName())) {
                return Integer.compare(h1.getAge(), h2.getAge());
            } else {
                return h1.getName().compareTo(h2.getName());
            }
        }
        public static void main(String args[]) {
            ...
            humans.sort(CmpDemo3::byNameThenAge);
        }
    }
```

4. 使用 `Comparator.comparing()`

用一个 instance method reference 和 `Comparator.comparing()` 方法，而不用实际定义比较逻辑。

直接使用：

```java
    Collections.sort(humans, Comparator.comparing(Human::getName));
```

赋给变量，注意类型是 `Comparator<T>`。

```java
    Comparator<Employee> byName = Comparator.comparing(Employee::getName);
    Arrays.sort(employees, byName);
```

不使用 natural ordering，自己提供一个 custom 比较方式。

```java
    Comparator<Employee> byNameReversed = Comparator.comparing(
            Employee::getName, (s1, s2) -> {
                return s2.compareTo(s1);
            });
        
    Arrays.sort(employees, employeeNameComparator);
```

比较整数类型，用 `comparingInt()`。类似的还有 `comparingLong()`，`comparingDouble()` 等。

```java
    Comparator<Employee> byAge = Comparator.comparingInt(Employee::getAge);
    Arrays.sort(employees, byAge);
```

5. 逆序

在已定义好的 comparator 基础上，用 `.reversed()` 可逆转顺序，省得再定义一个 comparator。

```java
    Comparator<Human> byName = (h1, h2) -> h1.getName().compareTo(h2.getName());
    humans.sort(byName.reversed());
```

6. 多个比较条件

```java
    humans.sort(
        Comparator.comparing(Human::getName).thenComparing(Human::getAge)
    );

    Comparator<Employee> byNameThenAge
        = Comparator.comparing(Employee::getName).thenComparingInt(Employee::getAge);
    Arrays.sort(someMoreEmployees, byNameThenAge);
```

7. 用 `Stream.sorted()` 对 List 排序 (Java 8)

若用 natural ordering，使用不带参数的 `sorted()`，此时 List 成员的类需实现 Comparable interface。

若自定义比较方式，用带参数的 `sorted(Comparator<? super T> comparator)`。

```java
    // natural orderding, sorted() 不带参
    List<String> l = letters.stream().sorted().collect(Collectors.toList());

    // custom ordering, sorted() 带参
    Comparator<Human> byName = (h1, h2) -> h1.getName().compareTo(h2.getName());
    List<Human> sortedHumans = humans.stream()
            .sorted(byName)
            .collect(Collectors.toList());

    // custom ordering, sorted() 带参, 简化，使用 Comparator.comparing()
    List<Human> sortedHumans = humans.stream()
            .sorted(Comparator.comparing(Human::getName))
            .collect(Collectors.toList());

    // custom ordering, 逆序
    List<String> reverseSortedLetters = letters.stream()
            .sorted(Comparator.reverseOrder())
            .collect(Collectors.toList());

    // custom ordering, 手工定义逆序 comparator
    Comparator<Human> byNameReversed = (h1, h2) -> h2.getName().compareTo(h1.getName());
    List<Human> reverseSortedHumans = humans.stream()
            .sorted(byNameReversed)
            .collect(Collectors.toList());

    // custom ordering, 使用 Comparator.comparing() + 逆序
    List<Human> reverseSortedHumans = humans.stream()
            .sorted(Comparator.comparing(Human::getName, Comparator.reverseOrder()))
            .collect(Collectors.toList());
```

8. Null Values

以上，都没考虑 null 的情况，`sort()` 遇到 null 会抛出 `NullPointerException`。

可以在 Comparator 实现中，手工处理 null 值。下面例子，认为 null > non-null, null == null.

```java
    humans.sort((h1, h2) -> {
        if (h1 == null) {
            return h2 == null ? 0 : 1;
        }
        if (h2 == null) {
            return -1;
        }
        return h1.getName().compareTo(h2.getName());
    });
```

另外，`Comparator.nullsLast()` 表示 null 值最大，`Comparator.nullsFirst()` 表示 null 值最小。

```java
    humans.sort(Comparator.nullsLast(Comparator.comparing(Human::getName)));

    humans.sort(Comparator.nullsFirst(Comparator.comparing(Human::getName)));
```
