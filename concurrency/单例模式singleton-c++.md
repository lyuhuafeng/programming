# 单例模式 singleton by c++

确保一个类只有一个实例；这个实例是「全局可访问的」；提供一个「全局访问点」来获取这个唯一实例。

常用于：日志记录、数据库连接、配置管理等场景

典型代码

```cpp
    class Singleton {
    private:
        static Singleton* instance_; // 静态指针，指向单例对象
        Singleton() {} // 私有构造函数，防止外部实例化
        Singleton(const Singleton&) = delete; // 禁止拷贝构造
        Singleton& operator=(const Singleton&) = delete; // 禁止拷贝赋值

    public:
        // 获取单例对象的静态方法
        static Singleton* getInstance() {
            if (instance_ == nullptr) {
                instance_ = new Singleton();
            }
            return instance_;
        }

        // 其他成员函数
        void doSomething() { ... }
    };

    // 初始化静态成员变量
    Singleton* Singleton::instance_ = nullptr;
```

法二：利用 std::call_once() 和 std::once_flag

[代码](code/singleton-call-once.cpp)

法三：利用 block scope 的静态变量，Meyers singleton

最佳

static 的 local 变量，其初始化发生在 control path 第一次经过其 declaration 时。c++11 之前，可能有 race condition，多个线程都可能认为自己先经过。c++11 之后，确保了其唯一性。所以，有些场景下，可用 static 变量来代替 call_once。

[代码](code/singleton-meyers.cpp)

为什么不直接使用全部是 static 成员的单例类，而要实例化一个对象？

- 面向对象原则（更倾向于使用「对象」而不是「类的 static 成员」）：静态成员虽然可实现「全局唯一」，但并不属于任何一个实例。我们更倾向于通过对象来封装数据和操作，而不直接使用静态成员。
- 生命周期：可控制对象何时创建（第一次访问该对象时，lazy initialization）、何时销毁（不再需要时）。对比：静态成员，程序启动时创建，程序结束时销毁，无法控制时机。（当然，很多时候无需提前销毁）
- 线程安全：在多线程环境中，静态初始化可能引发 race-condition。C++ 11 保证了静态局部变量的线程安全性，但在某些复杂场景下，显式控制单例对象的创建可提供更好的线程同步。
- 可扩展性、可测试性：对象，可更容易地扩展和修改类，因为可以像处理普通对象一样处理单例对象。在单元测试中，可能需要模拟或替换单例对象，以方便测试。通过实例化一个对象而不是使用静态成员，更容易些。


# 线程安全地初始化变量

方法：
- Constant expressions
- 用 std::call_once() 结合 std::once_flag
- 用 block scope 的静态变量
- 最简单：在 main 线程中初始化，然后再调用任何子线程。

```cpp
class MyDouble {
private:
    double myVal1;
    double myVal2;
public:
    constexpr MyDouble(double v1, double v2): myVal1(v1), myVal2(v2){}
    constexpr double getSum() const { return myVal1 + myVal2; }
};
int main() {
    constexpr double myStatVal = 2.0;
    constexpr MyDouble myStatic(10.5, myStatVal);
    constexpr double sumStat = myStatic.getSum();
}
```