
- java 8 `java.util.Optional<T>`
- c++ 17 `std::optional<T>`

问题：返回值是「无」，如何表示？

常见的：null, -1, 或 errcode。

若返回 null（null reference 常用来表示 absense of a value），容易引发 null pointer exception。

可将 Optional 看做一个 single-value container，或者存放了一个 value，或者是空的。

# c++

## 初始化

```c++
// 初始化为空，再用 emplace() 插入有效值
    std::optional<int> emptyInt;
    std::optional<int> emptyInt2 = {};
    std::optional<double> emptyDouble = std::nullopt;
    emptyInt.emplace(128);

// 直接用有效值初始化
    std::optional<int> intOpt{10};
    std::optional intOptDeduced{10.0}; // auto deduced

// 用 make_optional
    auto doubleOpt = std::make_optional(10.0);
    auto complexOpt = std::make_optional<std::complex<double>>(3.0, 4.0);

// 用 in_place
    std::optional<std::complex<double>> complexOpt{std::in_place, 3.0, 4.0};
    std::optional<std::vector<itn>> vectorOpt{std::in_place, {1, 2, 3}};

// 用其它 optional 对象构造
    auto optCopied = vectorOpt;
```

注意，std::optional 的一个构造函数接受右值引用 T&& 作为参数：

```c++
    template <typename T>
    constexpr optional(T&& value);

    std::optional<std::string> strOpt {"hello world"};
```

那为何还需要 in_place / make_optional 来对 optional 对象做「原地」构造呢？主要处理下面 3 种情形：
- optional 存储的对象，需用默认构造函数做构造
- optional 存储的对象，不支持拷贝和移动（non-copyable，non-movable）
- 构造函数有多个参数时，能提高构造效率

## optional 对象作为函数返回值

```c++
    std::optional<int> find_student(const std::map<std::string, int>& m, const std::string& name) {
	    return (m.count(name) > 0) ? m[name] : std::nullopt;
    }
    // 使用
    auto student_id = find_student(students, "Bob");
```

## 访问 optional 对象里存储的内容

```cpp
// 用 * 得到内部对象的引用，或 -> 得到内部对象的指针
// 但若 optional 对象里是空的，则行为是 undefined
    std::optional<std::string> opt{"abc"};
    std::cout << "content is " << *opt << ", size is " << opt->size() << std::endl;

// value() 返回内部存储对象的值，当 optional 为空时，抛出 std::bad_optional_access 异常
    try {
	    std::cout << "content is " << opt.value() << std::endl;
    } catch (const std::bad_optional_access & e) {
	    std::cout << e.what() << std::endl;
    }

// value_or(default_value): 若为空，则返回默认值
    std::optional<int> optInt(100);
    std::cout << "value is " << optInt.value_or(10) << std::endl;

// 也可用下面三种方法之一先判断是否为空，再取值使用
    if (res.has_value()) { std::cout << result1.value() << std::endl; }
    if (res != std::nullopt) {}
    if (res) {}
```

## 修改所存之值

可调用 optional 对象的 emplace, reset, swap, operator=。

其中，operator= 和 reset 可将 optional 对象赋值为 nullopt。

optional 对象内的原来对象（若不为空）的析构函数会被调用。

## 比较大小

若所存对象类型定义了 <，>，== 操作符，则 optional 对象也可比较大小。

特殊地，`std::nullopt` 总小于非空的 optional 对象。

## 内存

optional 对象，除了存储原对象，还有一个额外的 bool flag，因此 optional 对象占内存更多。

optional 对象的内存排列，遵循与内部对象一致的内存对齐准则。

## 另一个例子

```c++
    std::optional find_by_model(std::string model) {
        const auto found = database.execute_query(...);
        return found.has_result() ? std::make_optional(car.from_row(found)) : std::nullopt;
    }
    
    // Somewhere else...
    const auto found_car = find_by_model("i30 N");
    if (!found_car.has_value()) {
        throw not_found_exception{};
    }
    found_car.value().drive();
    found_car->drive(); // 此写法更好
```

# java

参考 [java 官方文档](https://www.oracle.com/technical-resources/articles/java/java8-optional.html)

```java
    public class Computer {
        private Optional<Soundcard> soundcard;  
        public Optional<Soundcard> getSoundcard() { ... }
    }

    public class Soundcard {
        private Optional<USB> usb;
        public Optional<USB> getUSB() { ... }
    }

    public class USB {
        public String getVersion(){ ... }
    }

    String name = computer.flatMap(Computer::getSoundcard)
                          .flatMap(Soundcard::getUSB)
                          .map(USB::getVersion)
                          .orElse("UNKNOWN");
```

## 创建 Optional 对象

都是静态类方法，返回值都是 `Optional<T>` 类型。

```java
    Optional<Soundcard> sc = Optional.empty(); // 空的
    Optional<Soundcard> sc = Optional.of(new Soundcard()); // 非空的
    Optional<Soundcard> sc = Optional.ofNullable(soundcard); // 可能空，根据 soundcard 的值
```

## 从 optional 中取出 value，或 ...

这些方法的返回值，都是 value 的类型 T。

- `orElse(other)`: 返回 value，或返回 other
- `orElseGet(supplier)`: 返回 value，或返回 `supplier()` 的执行结果
- `orElseThrow()`, `get()`: 返回 value，或抛出 `NoSuchElementException`。注意，`get()` 已被前者取代。
- `orElseThrow​(supplier)`: 返回 value，或抛出 `supplier()` 的执行结果

可理解为，若 value 不存在，则返回个 default 值。例：

```java
// 使用 Optional
    Soundcard soundcard = maybeSoundcard.orElse(new Soundcard("my_card"));
    Soundcard soundcard = maybeSoundCard.orElseThrow(IllegalStateException::new);

// 作为对比，不使用 Optional
    Soundcard soundcard = (maybeSoundcard != null) ? maybeSoundcard : new Soundcard("my_card");
```

## 从 optional 中返回 optional，或 ...

返回值是 `Optional<T>` 类型。

- `or(supplier)`: 返回 `optional.of(value)`，或返回 `supplier()` 的结果（optional 类型的）

## 对 optional 中的 value 做点啥，或 ...

无返回值。

- `ifPresent(action)`: 执行 `action(value)`，或啥也不干
- `ifPresentOrElse(action, emptyAction)`: 执行 `action(value)`，或执行 `emptyAction(value)`

```java
// 作为对比：不使用 Optional 的方式
    SoundCard soundcard = ...;
    if (soundcard != null) {
        System.out.println(soundcard);
    }

// 使用 Optional 
    Optional<Soundcard> soundcard = ...;
    soundcard.ifPresent(System.out::println);

// 使用 Optional 方式二，有点笨
    if (soundcard.isPresent()) {
        System.out.println(soundcard.get());
    }
```

## 过滤

`filter()` 返回类型是 `Optional<T>`，或为原 value，或为 empty。

```java
// 使用 Optional
    Optional<USB> maybeUSB = ...;
    maybeUSB.filter(usb -> "3.0".equals().usb.getVersion())
            .ifPresent(() -> System.out.println("ok"));

// 作为对比，不使用 Optional
    USB usb = ...;
    if (usb != null && usb.getVersion().equals("3.0")) {
        System.out.println("ok");
    }
```

## map 和 flatMap

```java
    Optional<USB> usb = maybeSoundcard.map(Soundcard::getUSB);
```

- (1) optional 对象中存储的对象（soundcard），map 一下（通过调用 map 参数指定的 getUSB() 方法），结果还放到另一个 optional 中。
- (2) 注意，nothing happens if Optional is empty。<font color=red>啥也不发生，最后得到的 usb 值是 empty optional.</font>

与 stream 很像。只不过 stream 中可能有多个或 0 个对象，而 optional 对象中只能有 1 个或 0 个对象。
- (1) stream 中的每个对象，map 一下（通过调用 map 参数指定的方法），结果都还放到一个新的 stream 中。
- (2) nothing happens if the stream is empty。

map 实现了 checking for null and extracting 的模式。

```java
// 与 filter 结合使用
    maybeSoundcard.map(Soundcard::getUSB)
                  .filter(usb -> "3.0".equals(usb.getVersion()))
                  .ifPresent(() -> System.out.println("ok"));
```

flatMap(): 用于嵌套的 optional 对象

```java
// 错误用法
    String version = computer.map(Computer::getSoundcard) // 得到 Optional<Optional<Soundcard>>
                  .map(Soundcard::getUSB) // 出错
                  .map(USB::getVersion)
                  .orElse("UNKNOWN");
```

`computer.getSoundcard()` 返回值是 `optional<SoundCard>`，所以第一行的 `computer.map()` 的结果是 `Optional<Optional<SoundCard>>`。随后，第二行的 `map()` 试图调用 `Optional<SoundCard>` 的 `getUSB()` 方法，该方法不存在，出错。

解决方法，用 `flatMap()`。它对 optional 里的对象应用了 flatMap 参数指定的方法后，不会把结果再放入 optional。如下：

```java
// 正确用法
    String version = computer.flatMap(Computer::getSoundcard)
                             .flatMap(Soundcard::getUSB)
                             .map(USB::getVersion)
                             .orElse("UNKNOWN");
```

与 stream 的 `flatMap()` 类似：
- stream 中的每个 object -> 一个含多个 object 的 stream
- 这些「小 stream」被 flatten（其中中的 object 被取出）合并到一个 stream 中

只不过 Optional 中最多有一个 value，所以 flatten 的效果是：
- Optional 中的每个（唯一一个）value -> 一个含一个 value 的 Optional
- 这个「小 Optional」被 flatten（其中的 value 被取出）合并到一个 Optional 中

stream `flatMap()` 的例子：

```java
// 定义
    class Person {
        private String name;
        private List<String> colors;
    }
    List<Person> people = Arrays.asList(
            new Person("Alice", Arrays.asList("Red", "Blue")),
            new Person("Bob", Arrays.asList("Green", "Yellow")),
            new Person("Charlie", Arrays.asList("Purple"))
        );

// 用 map，得到三个 stream 组成的 stream，对应 List<List<String>>
    List<List<String>> allColors = people.stream()
            .map(Person::getColors)
            .collect(Collectors.toList());
    // 结果为：[ [Red, Blue], [Green, Yellow], [Purple] ]

// 用 flatMap，三个 stream 被 flatten 合并，得到一个 stream，对应 List<String>
    List<String> allColors = people.stream()
            .flatMap(person -> person.getColors().stream())
            .collect(Collectors.toList());
    // 结果为：[Red, Blue, Green, Yellow, Purple]
```        


## 例

```java
// 使用 optional 的方式
    return Optional.ofNullable(user)
                   .map(u -> u.getUsername())
                   .map(name -> name.toUpperCase())
                   .orElse(null);

// 同样功能，不用 optional 的方式：
    User user = .....
    if (user == null) {
        return null;
    }
    String name = user.getUsername();
    if (name == null) {
        return null;
    }
    return name.toUpperCase();
```
