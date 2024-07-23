#include <iostream>
using namespace std;

/*
 block scope 的静态变量的好特性：
 - 只创建一次
 - lazy 创建
 - 初始化是 thread-safe 的 (since c++11)

 static 的 local 变量，其初始化发生在 control path 第一次经过其 declaration 时。
 c++11 之前，可能有 race condition，多个线程都可能认为自己先经过。
 c++11 之后，确保了其唯一性。所以，有些场景下，可用 static 变量来代替 call_once。
 
 利用此特性实现的 singleton，称为 Meyers Singleton。(Scott Meyers) 是 c++ singleton 最佳实现方式
*/
class MySingleton {
private:
    MySingleton() = default;
    ~MySingleton() = default;
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

public:
    static MySingleton& getInstance() {
        static MySingleton inst;
        return inst;
    }

    void do_something() { /* ... */ }
};

// 为何在这里初始化，而不是在类里？
// MySingleton::() = default;
// MySingleton::~MySingleton() = default;

int main() {
    cout << "MySingleton::getInstance(): " << &MySingleton::getInstance() << '\n';
    cout << "MySingleton::getInstance(): " << &MySingleton::getInstance() << '\n';
    return 0;
}

