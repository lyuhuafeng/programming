#include <iostream>
#include <mutex>
using namespace std;

class MySingleton{
private:
    static std::once_flag initInstanceFlag;
    static MySingleton* instance;
    
    MySingleton() = default;
    ~MySingleton() = default;

    static void initSingleton() {
        instance = new MySingleton();
    }
public:
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

    static MySingleton* getInstance(){
        std::call_once(initInstanceFlag, MySingleton::initSingleton);
        return instance;
    }

    void do_something() { /* ... */ }
};

// 为何在这里初始化，而不是在类里？
MySingleton* MySingleton::instance = nullptr;
std::once_flag MySingleton::initInstanceFlag;

int main() {
    cout << "MySingleton::getInstance(): "<< MySingleton::getInstance() << '\n';
    cout << "MySingleton::getInstance(): "<< MySingleton::getInstance() << '\n';
    return 0;
}

