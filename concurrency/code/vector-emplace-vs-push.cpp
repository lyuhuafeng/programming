#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

class myclass {
private:
    int a;
    std::string s;
    float b;

public:
    myclass(int a_, std::string s_, float b_) : a(a_), s(s_), b(b_) {
        printf("regular constructor\n");
    }
    myclass(const myclass &c) : a(c.a), s(c.s), b(c.b) {
        printf("copy constructor\n");
    }
    myclass(myclass&& c) {
        printf("move constructor\n");
        a = c.a;
        s = std::move(c.s); // 移动字符串
        b = c.b;
    }
    ~myclass() {
        printf("destroyed\n");
    }

    std::string to_string() { return std::to_string(a) + "," + s + "," + std::to_string(b); }
};

int main() {
    std::vector<myclass> v;

    // (B) push_back() 经典写法
    myclass c(3, "hello", 1.41); // regular 构造
    v.push_back(c); // copy 构造
    // 程序结束时，析构两次
    
    // (C) push_back() 显式使用 move 构造
    myclass c(3, "hello", 1.41); // regular 构造
    v.push_back(std::move(c)); // move 构造
    // 程序结束时，析构两次

    // (A) push_back() 隐式使用 move 构造，代码也比经典写法更简洁
    v.push_back({3, "hello", 1.41});  // regular 构造一次（临时对象）, move 构造一次, 析构一次（临时对象）
    // 程序结束时，析构一次

    // (A) 最佳 emplace_back() 用法。
    v.emplace_back(3, "hello", 1.41); // regular 构造一次
    // 程序结束时，析构一次。

    // 编译错误
    // v.emplace_back({3, "hello", 1.41});

    // (B) emplace_back() 使用不当，调用了 copy 构造
    myclass c(3, "hello", 1.41); // regular 构造
    v.emplace_back(c); // copy 构造
    // 程序结束时，析构两次

    // (C) emplace_back() 显式调用 move 构造
    myclass c(3, "hello", 1.41); // regular 构造
    v.emplace_back(std::move(c)); // move 构造。此后，c.s 内容为空。
    std::cout << "c: " << c.to_string() << std::endl;
    std::cout << "v[0]: " << v[0].to_string() << std::endl;
    // 程序结束时，析构两次：应该是 c 和 v[0]

    return 0;
}