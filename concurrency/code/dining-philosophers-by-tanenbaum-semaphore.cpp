// concurrency with modern c++, section 6.2.14
// the Tanenbaum solution rewritten in c++20

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <semaphore>
#include <random>

int myrand(int min, int max) {
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min,max)(rnd);
}

enum {
    N = 5,        // number of philosophers
    THINKING = 0, // philosopher is thinking
    HUNGRY = 1,   // philosopher is trying to get forks
    EATING = 2,   // philosopher is eating
};

// i: philosopher number, from 0 to N-1
inline int LEFT(int i) { return (i + N - 1) % N; }
inline int RIGHT(int i) { return (i + 1) % N; }

int state[N]; // array to keep track of everyone's state
std::mutex mutex_; // mutual exclusion for critical regions

std::binary_semaphore s[] = {
    std::binary_semaphore(0),
    std::binary_semaphore(0),
    std::binary_semaphore(0),
    std::binary_semaphore(0),
    std::binary_semaphore(0)
}; // one semaphore per philosopher

// i: philosopher number, from 0 to N-1
void test(int i) {
    if (state[i] == HUNGRY && state[LEFT(i)] != EATING && state[RIGHT(i)] != EATING) {
        state[i] = EATING;
        s[i].release();
    }
}

// i: philosopher number, from 0 to N-1
void take_forks(int i) {
    mutex_.lock();     // enter critical region
    state[i] = HUNGRY; // record fact that philosopher i is hungry
    test(i);           // try to acquire 2 forks
    mutex_.unlock();   // exit critical region
    s[i].acquire();    // block if forks were not acquired
}

// i: philosopher number, from 0 to N-1
void put_forks(int i) {
    mutex_.lock();       // enter critical region
    state[i] = THINKING; // philosopher has finished eating
    test(LEFT(i));       // see if left neighbor can now eat
    test(RIGHT(i));      // see if right neighbor can now eat
    mutex_.unlock();     // exit critical region
}

std::mutex mtx;

void think(int i) {
    int duration = myrand(1000, 2000);
    {
        std::lock_guard<std::mutex> g(mtx);
        std::cout << i << " thinks " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void eat(int i) {
    int duration = myrand(1000, 2000);
    {
        std::lock_guard<std::mutex> g(mtx);
        std::cout << "\t\t\t\t" << i << " eats " << duration << "ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void philosopher(int i) {
    while (true) { // repeat forever
        think(i);      // philosopher is thinking
        take_forks(i); // acquire two forks or block
        eat(i);
        put_forks(i);  // put both forks back on table
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(philosopher, i);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
