#include <future>
#include <iostream>
#include <thread>
#include <utility>
using namespace std;

void product(promise<int>&& int_promise, int a, int b) {
    int_promise.set_value(a * b);
}

struct Div {
    void operator() (promise<int>&& int_promise, int a, int b) const {
        int_promise.set_value(a / b);
    }
};

int main() {
    int a = 20, b = 10;

    // 1: 乘法, 2: 除法
    promise<int> p1, p2;

    future<int> res1 = p1.get_future();
    future<int> res2 = p2.get_future();

    thread t1(product, std::move(p1), a, b);
    Div div;
    thread t2(div, std::move(p2), a, b);

    printf("20 * 10 = %d\n20 / 10 = %d\n", res1.get(), res2.get());

    t1.join();
    t2.join();
    return 0;
}
