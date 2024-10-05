#include <iostream>
#include <unordered_map>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

std::unordered_map<std::string, int> tele_book {
    {"Dijkstra", 1972},
    {"Scott", 1976},
    {"Ritchie", 1983}
};

std::shared_timed_mutex mtx;

void addToTeleBook(const std::string& na, int tele) {
    std::lock_guard<std::shared_timed_mutex> wlock(mtx);
    std::cout << "\nSTARTING UPDATE " << na;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    tele_book[na]= tele;
    std::cout << " ... ENDING UPDATE " << na << std::endl << std::endl;
    fflush(stdout);
}

void printNumber(const std::string& na){
    std::shared_lock<std::shared_timed_mutex> rlock(mtx);

    // 不能直接用 [] 访问！若 key 不存在，会创建一个，是写操作！会导致 race condition!
    // std::cout << na << ": " << tele_book[na] << std::endl; // 错误！

    // 正确做法
    auto it = tele_book.find(na);
    if (it != tele_book.end()) {
        std::cout << na << ": " << it->second << std::endl; 
    } else {
        std::cout << na << ": not found" << std::endl;
    }
    fflush(stdout); // 加了刷新，但输出结果还是会掺到一起，因为各 reader 之间可同时进行
}

int main() {
    std::vector<std::thread> threads;
    threads.emplace_back(printNumber, "Scott");
    threads.emplace_back(printNumber, "Ritchie");
    threads.emplace_back(addToTeleBook, "Scott", 1968);
    threads.emplace_back(printNumber, "Dijkstra");
    threads.emplace_back(printNumber, "Scott");
    threads.emplace_back(addToTeleBook, "Bjarne", 1965);
    threads.emplace_back(printNumber, "Scott");
    threads.emplace_back(printNumber, "Ritchie");
    threads.emplace_back(printNumber, "Scott");
    threads.emplace_back(printNumber, "Burne");
    threads.emplace_back(printNumber, "Bjarne");
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
