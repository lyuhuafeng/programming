#include <exception>
#include <memory> // std::shared_ptr
#include <stack>
#include <mutex>

// c++ concurrency in action, chapter 6.2.1

// 每个成员函数都用 mutex 保护（该函数的第一个操作），保证任何时刻都只有一个线程在访问 st。
// 上锁本身也可能抛出异常，但不用考虑。说明 mutex 有问题，或整个系统缺资源了。
// pop() 之前不用调 empty() 了；top()、pop() 合二为一了，消除了 race condition。

// (1)(3)(5) 处的 copy/move constructor，以及可能用户自定义的 new，是用户的代码，在持有锁时调用，可能 deadlock。
// 调用方需要正确使用。
    // If these functions _either_ call member functions on the stack 
    // that the item is being inserted into or removed from 
    // _or_ require a lock of any kind and another lock was held 
    // when the stack member function was invoked, 
    // there’s the possibility of deadlock. 
// 构造函数、析构函数：没有 lock 保护，可能不安全。用户确保：彻底构造好后，再被其他线程调用。
// 性能：拿不到锁，只能等，不停自己写代码轮询。解法：用 condition variable，把「等」也变成数据结构的一部分。

struct empty_stack_exception: std::exception {
    const char* what() const noexcept;
};

template<typename T>
class threadsafe_stack {
private:
    std::stack<T> st;
    mutable std::mutex mtx;
public:
    threadsafe_stack() {}

    // copy constructor
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> guard(other.mtx); // 注意是用的对方的 mtx
        st = other.st; // 在函数体内赋值，而不放在 initializer list 中，为了在整个 copy 过程中都持有 mtx。
    };

    threadsafe_stack& operator=(const threadsafe_stack&) = delete; // 赋值运算符：删掉

    void push(T val) {
        std::lock_guard<std::mutex> guard(mtx);
        st.push(std::move(val)); // (1) 注意是 move。若 copy/move 抛异常，或内存不够，则 push 抛异常。但仍然安全。
    }

    // option 3: 返回对象的 shared_ptr
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> guard(mtx);
        if (st.empty()) {
            throw empty_stack_exception(); // (2) 即使抛异常，也没修改任何数据，所以安全。
        }
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(st.top()))); // (3)
        // 两种情况可能导致抛异常。但没修改任何数据，所以安全。
        //     (a) make_shared 需给新对象分配内存，若内存不够，可能抛异常。
        //     (b) 分配内存后，copy/move 可能抛异常。

        st.pop(); // (4) 不会抛异常
        return res;
    }

    // option 1: 传入引用
    void pop(T& val) {
        std::lock_guard<std::mutex> guard(mtx);
        if (st.empty()) {
            throw empty_stack_exception();
        }
        val = std::move(st.top()); // (5) copy/move constructor 可能抛异常，但没修改任何数据，所以安全
        // 若 T 是个结构体，可否分别给其成员赋值？但泛型情况下，不知其内部结果，无法，只能直接赋值或 move
        st.pop(); // (6) 不会抛异常
    }

    bool empty() const {
        std::lock_guard<std::mutex> guard(mtx);
        return st.empty(); // 不修改任何数据，所以安全
    }
};

int main() {}