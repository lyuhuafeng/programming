
痛点：临时对象 temporary object 的创建

有时，temporary objects 可被编译器优化掉。例如：the return value optimization (RVO)。

为支持 move semantics，引入了：
- rvalue references
- move constructor
- move assignment operator
- stl 工具，如 `std::move()`, `std::forward()`, etc

To appreciate the use of move semantics, we need to know the scope of it, which brings us to the topic of rvalue and lvalue.

move semantics 建立在 rvalue reference 之上。

```cpp
    vector<int> doubleValues (const vector<int>& v) {
        vector<int> new_values;
        new_values.reserve(v.size());
        for (auto it = v.begin(); it != v.eng(); it++) {
            new_values.push_back(2 * (*it));
        }
        return new_values; // 1
    }

    // 调用    
    vector<int> v2 = doubleValues(v); // 2
```

1. 把 new_values 拷贝一份，并返回之
2. 返回结果，拷贝一份，赋值给 v2。然后返回结果被扔掉。



# lvalue, rvalue

In C++ an lvalue is something that points to a specific memory location. On the other hand, a rvalue is something that doesn't point anywhere. In general, rvalues are temporary and short lived, while lvalues live a longer life since they exist as variables. It's also fun to think of lvalues as containers and rvalues as things contained in the containers. Without a container, they would expire.

Let me show you some examples right away.

非正式定义，容易理解：
lvalue
- 对应一个内存地址（memory location）
- 以变量形式存在，生命周期长
- 可出现在等号左边或右边

rvalue
- 不对应内存地址。例如 `int x = 6` 中的 `6`，可能在程序运行时的某临时 register 中。
- temporary, short-lived。无法改变（因不是变量）
- 只能出现在等号右边

更正式的定义：来自 https://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/

lvalue (locator value): 是个有地址的对象。an object that occupies some identifiable location in memory (i.e. has an address)
rvalue: 一个表达式，不是 lvalue 的。所以，rvalue 是临时的，可能在程序运行时存在临时 register 中。它所在的那行代码执行完后，rvalue 就被扔掉了。

历史上，l 只能出现在左边，r 只能出现在右边。现在不是了。

there are lvalues that cannot appear on the left-hand side of an assignment (like arrays or user-defined types without an assignment operator), and there are rvalues which can (all rvalues of class types with an assignment operator).

An rvalue of class type is an expression whose evaluation creates a temporary object. Under normal circumstances, no other expression inside the same scope denotes the same temporary object.

`string name = getName();`
But you're assigning from a temporary object, not from some value that has a fixed location. getName() is an rvalue.

## 返回 lvalue 和 rvalue 的函数

```cpp
    int setValue() { return 6; } // 返回 rvalue
    setValue() = 3; // 错误！返回的 rvalue 不能出现在等号左边，不能被赋值！

    int global = 100;
    int& setGlobal() { return global; } // 返回 lvalue
    setGlobal() = 400; // 正确！返回的 lvalue 可以被赋值
```

# rvalue reference

- rvalue: 不可改变
- rvalue refernence: 一种新类型，可 bind 到临时对象上，从而可改变这些临时变量的值

传统 c++：可以取 rvalue 的地址，但只能赋给 const (immutable) 变量。更严谨地说法：可以 bind a const lvalue to an rvalue。如下：

```cpp
    int& x = 666;       // Error
    const int& x = 666; // OK
```

since c++11，使用 rvalue reference:

```cpp
    std::string&& s_rref = s1 + s2; // s_rref 是个 rvalue
    s_rref += ", my friend"; // 可以改变
```

c++11 之前，没有 rvalue reference 的概念。临时对象（也就是 rvalue）只能赋给 const lvalue reference，不能赋给 mutable 的。因为马上就消失了，修改没意义。
```cpp
    const string& name = getName(); // ok: const lvalue reference
    string& name = getName(); // NOT ok: mutable lvalue reference
```

c++11 之后，有了 rvalue reference。rvalue 可以赋给 const 或 mutable 的 rvalue reference。
```cpp
    const string&& name = getName(); // ok: const rvalue reference
    string&& name = getName(); // also ok: mutable rvalue reference
```

隐式转换成 rvalue reference 的例子：
```cpp
    void some_function(std::string&& r);
    some_function("hello world");
```

但，注意！lvalue reference 和 rvalue reference 都是 lvaue expression！

# move constructor

ref: https://stackoverflow.com/questions/3106110/what-is-move-semantics

https://stackoverflow.com/questions/3106110/what-is-move-semantics/11540204#11540204

有了 rvalue reference，其常见用途就是用在 move constructor 和 move assignment operator 里。

```cpp
    class ArrayWrapper {
    private:
        int *vals;
        int size;

    public:
        // move constructor: 直接用了 other 的指针，并把对方的指针置为空。反正对方是临时的，以后也没用了。
        // 修改了对方的状态，所以对方必须不能是 const 的。
        // 为何要把对方指针置空？因为对方毕竟也是个 object，销毁时还是会调用析构函数，会释放内存。
        // 所以其实可以直接用 std::swap() 交换指针，但为了代码清晰，还是用置空。
        ArrayWrapper(ArrayWrapper&& other) : vals(other.vals), size(other.size) {
            other.vals = nullptr;
            other.size = 0;
        }
    }
```

如果成员不是指针，而是个普通对象。得用 std::move() 才行。

std::move() 的唯一作用，无论输入是 lvalue 还是 rvalue，都转换成 rvalue。

std::move() 本质上是个 type casting，用了 static_cast。

std::move(s) 把 s 标记为 moveable，意为「I no longer need this value here」。但并不真正移动。随后，将该 moveable 对象用于触发 move constructor 或 move assignment operator，对方可能直接利用（移走）moveable object 中已分配的资源（并将 moveable object 中相应字段置为 nullptr），则该 moveable object 就变成不可用了。

moved-from object 处在 valid but unspecified 的状态中。

```cpp
    class MetaData {
    private:
        std::string name;
        int size;
    public:
        // move constructor: 错误写法！
        MetaData (MetaData&& other) : name(other.name), size(other.size) {}
        // move constructor: 正确写法！
        MetaData (MetaData&& other) : name(std::move(other.name)), size(other.size) {}
    };

    class ArrayWrapper {
    private:
        int *vals;
        MetaData md;
    public:
        // move constructor: 错误写法！
        // 想在 move constructor 调用 MetaData 的 move constructor，
        // 但 other 是 rvalue reference，但不是 rvalue，而是 lvalue
        // 所以，调用的是 md 的 copy constructor，而不是 move constructor
        ArrayWrapper(ArrayWrapper&& other) : vals(other.vals), md(other.md) {
            other.vals = nullptr;
        }

        // move constructor: 正确写法！
        ArrayWrapper(ArrayWrapper&& other) : vals(other.vals), md(std::move(other.md)) {
            other.vals = nullptr;
        }
    }
```

# move assignment operator

以 unique_ptr 为例

```cpp
    // 普通写法
    unique_ptr& operator=(unique_ptr&& source) { // 注意有 &&，是 rvalue reference
        if (this != &source) {
            delete ptr;         // release the old resource
            ptr = source.ptr;   // acquire the new resource
            source.ptr = nullptr;
        }
        return *this;
    }
    // 或用 move-and-swap idiom
    unique_ptr& operator=(unique_ptr source) { // 但为啥这里没有 &&
        std::swap(ptr, source.ptr);
        return *this;
        // 本函数结束时，source 被销毁，不用显式调 delete
    }
```


#

```cpp
    // 普通：返回 value。返回的是个 rvalue
    int getInt() {
        return x;
    }
    // 显式返回 rvalue reference
    int && getRvalueInt() {
        return std::move(x);
    }
```

两者不一样。但通常也没必要显式返回 rvalue reference。（危险：dangling reference：悬空引用，正主已经没了，reference 还在）

何时需要显式返回 rvalue reference？某 class 有个成员函数，需要从该函数返回该类某成员调用 std::move() 的结果。很少需要这样做。

# perfect forward

https://www.cnblogs.com/sinkinben/p/15901997.html

# universal reference


xvalue - "eXpiring value", it usually refers to an object, usually near the end of its lifetime (so that its resources may be moved).

e.g. suppose we have a function auto f() { return string("hello")}, and we let str += f(), where f() is a xvalue (also a rvalue).

universal reference: 可能被解析为 lvalue reference 或 rvalue reference

如何区分 universal reference 和 rvalue reference？他们都用 && 符号。
https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers


# vector push_back() vs. emplace_back()

- v.emplace_back(arg_list) <font color=red>最佳写法<font>。直接在 vector 尾部用 arg-list 构造一个对象。
- v.emplace_back(obj) 调用 obj 的 copy constructor（不知能够自动优化为 move constructor）
- v.emplace_back(std::move(obj)) 显式调用 obj 的 move constructor，比 copy constructor 性能好一些。
- v.push_back({arg-list}) 用 arg-list 构造一个临时对象，然后隐式调用 move constructor 放到 vector 尾部。
- v.push_back(obj) 是 push_back() 的经典用法，调用 obj 的 copy constructor
- v.push_back(std::move(obj)) 显式调用 obj 的 move constructor

[完整代码](code/vector-emplace-vs-push.cpp)

#

```cpp
    #include <utility>
    
    template <typename T>
    void myswap(T &a, T &b) noexcept {
        T t = std::move(a);
        a = std::move(b);
        b = std::move(t);
    }
```

# rule of three/five

rule of three, 又称为 the big three, the law of the big three

在 c++ 11 之前，如果一个 class 需要自定义 copy constructor、copy assignment operator 和 destructor 中的人一个，那最好把这三个函数都自定义。

c++ 11 引入了 move semantics，则 rule of 3 变成了 rule of 5：又增加了 move constructor 和 move assignment operator。

注意，把 move constructors 和 move assignment operators 标记为 noexcept，意为「此函数绝对不会抛出异常」，用于优化。注意，在这两个 move 函数中，不要分配内存，也不要调用任何可能抛出异常的代码。只应该 copy data 并把其他对象设置为 null，即 non-throwing 操作。[ref1](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#f6-if-your-function-may-not-throw-declare-it-noexcept), [ref2](https://stackoverflow.com/questions/9249781/are-move-constructors-required-to-be-noexcept)


# RVO (return value optimization)

编译器检测到函数 return object by value，会做优化，避免无用的复制。可用 -fno-elide-constructors 选项关闭此功能。

但，既然有了 RVO，可自动做优化，为何还要自己显式实现 move semantics？

因为 RVO 只是关于函数返回值（output），而不是函数参数（input），即，入参是 moveable objects 的情况。

# copy-and-swap idiom

All the constructors/assignment operators in the Holder class are full of duplicate code, which is not so great. Moreover, if the allocation throws an exception in the copy assignment operator the source object might be left in a bad state. The copy-and-swap idiom fixes both issues, at the cost of adding a new method to the class. [ref1](https://stackoverflow.com/a/3279550/3296421), [ref2](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap)

# ref

https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
