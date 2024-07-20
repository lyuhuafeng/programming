#include <iostream>
#include <string>
#include <mutex>
#include <thread>

std::mutex coutMutex;
thread_local std::string s("hello from "); // 此时创建，with first use

void addThreadLocal(std::string const& s2) {
    s += s2;
    // protect std::cout
    std::lock_guard<std::mutex> guard(coutMutex);
    std::cout << s << ", " << &s << std::endl << std::endl;
}
int main(){
    std::cout << "____begin " << s << ", " << &s << std::endl;
    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::cout << "____end " << s << ", " << &s << std::endl;
}
