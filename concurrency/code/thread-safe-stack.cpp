#include <exception>
#include <memory> // std::shared_ptr
#include <stack>
#include <mutex>

struct empty_stack: std::exception {
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
        st = other.st; // assignment，构造函数中用了 copy。不放在 initializer list 中，为了在 copy 过程中都持有 mtx。
    };

    threadsafe_stack& operator=(const threadsafe_stack&) = delete; // 赋值运算符：删掉

    void push(T val) {
        std::lock_guard<std::mutex> guard(mtx);
        st.push(std::move(val)); // 注意是 move
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> guard(mtx);
        if (st.empty()) {
            throw empty_stack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(st.top()));
        st.pop();
        return res;
    }

    void pop(T& val) {
        std::lock_guard<std::mutex> guard(mtx);
        if (st.empty()) {
            throw empty_stack();
        }
        val = st.top(); // 若 T 是个结构体，可否分别给其成员赋值？但泛型情况下，不知其内部结果，无法，只能直接赋值
        st.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> guard(mtx);
        return st.empty();
    }
};

int main() {}