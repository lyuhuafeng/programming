#include <iostream>
#include <mutex>
#include <barrier>
#include <thread>
#include <string>
#include <vector>

std::barrier workDone(6);
std::mutex coutMutex;

void synchronizedOut(const std::string s) {
    std::lock_guard<std::mutex> guard(coutMutex); 
    std::cout << s;
}

class FullTimeWorker {
private:
    std::string name;
public:
    FullTimeWorker(std::string n): name(n) {}

    void operator() () {
        synchronizedOut(name + ": " + "morning work done!\n");
        workDone.arrive_and_wait(); // Wait until morning work is done 
        synchronizedOut(name + ": " + "afternoon work done!\n"); 
        workDone.arrive_and_wait(); // Wait until afternoon work is done
    }
};
class PartTimeWorker {
private:
    std::string name;
public:
    PartTimeWorker(std::string n): name(n) {}

    void operator() () {
        synchronizedOut("    " + name + ": " + "morning work done!\n");
        workDone.arrive_and_drop();
    }
};

int main() {
    std::vector<std::thread> workers;
    for (const std::string &s : {"Herb", "Scott", "Bjarne"}) {
        workers.emplace_back(FullTimeWorker(s));
    }
    for (const std::string &s : {"Andrei", "Andrew", "David"}) {
        workers.emplace_back(PartTimeWorker(s));
    }

    for (std::thread &t : workers) {
        t.join();
    }
    return 0;
}
