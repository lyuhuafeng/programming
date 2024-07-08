#include <list>
#include <mutex>
#include <algorithm>
using namespace std;

list<int> l;
mutex mtx;

// 两个操作都用 lock_guard<mutex> 保护

void add_to_list(int val) {
    lock_guard<mutex> guard(mtx);
    l.push_back(val);
}

bool list_contains(int val) {
    lock_guard<mutex> guard(mtx);
    return find(l.begin(), l.end(), val) != l.end();
}