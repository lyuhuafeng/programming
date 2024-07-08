#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

mutex mtx;
condition_variable cv;
bool data_ready = false;

void producer() {
    printf("producer started.\n");
    this_thread::sleep_for(chrono::seconds(2));
    {
        lock_guard<mutex> guard(mtx);
        data_ready = true;
    }
    printf("data produced.\n");
    cv.notify_one();
}

void consumer() {
    printf("consumer started.\n");
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return data_ready; });
    printf("data consumed.\n");
}

int main() {
    thread tc(consumer);
    thread tp(producer);

    tc.join();
    tp.join();

    return 0;
}
