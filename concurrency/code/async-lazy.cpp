#include <chrono>
#include <future>
#include <iostream>
using namespace std;

chrono::system_clock::time_point get_now() {
    return chrono::system_clock::now();
}

int main() {
    auto begin = get_now();
    auto f_lazy = async(launch::deferred, get_now);
    auto f_eager = async(launch::async, get_now);
    // cout << "begin: " << begin << endl;

    this_thread::sleep_for(chrono::seconds(3));

    auto lazy_start = f_lazy.get() - begin;
    auto eaget_start = f_eager.get() - begin;
    // cout << lazyStart << endl;

    auto lazy_duration = chrono::duration<double>(lazy_start).count();
    auto eager_duration = chrono::duration<double>(eaget_start).count();

    cout << "lazy  evaluated after " << lazy_duration << " seconds." << endl;
    cout << "eager evaluated after " << eager_duration << " seconds." << endl;
    return 0;
}
