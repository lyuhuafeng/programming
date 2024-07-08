#include <thread>                         // std::thread
#include <mutex>                            // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <cstdio>                     // std::cout
using namespace std;

mutex mtx;
condition_variable cv;
bool data_ready = false;

void print_id (int id) {
    // printf("thread %d started\n", id);
    unique_lock<mutex> lck(mtx);
    while (!data_ready) {
        cv.wait(lck);
    }
    printf("thread %d \n", id);
}

void go() {
    // printf("thread go started\n");
    this_thread::sleep_for(chrono::seconds(3));
    unique_lock<mutex> lck(mtx);
    data_ready = true;
    printf("thread go to notify all\n");
    cv.notify_all();
    printf("thread go notified.\n");
}

int main () {
    thread threads[10];
    for (int i = 0; i < 5; ++i) {
        threads[i] = thread(print_id, i);
    }
    printf("threads created. will go.\n");
    go();
    printf("go called. will join\n");

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
