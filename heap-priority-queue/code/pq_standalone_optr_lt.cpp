#include <cstdio>
#include <queue>
using namespace std;

struct Person {
    int age;
    float height;
    Person(int a, float h): age(a), height(h) {}
};

bool operator<(const Person& p1, const Person& p2) {
    return p1.height < p2.height;
}

void display_pq(priority_queue<Person>& pq) {
    while (!pq.empty()) {
        Person p = pq.top();
        printf("%d, %f\n", p.age, p.height);
        pq.pop();
    }
}
void display_vec(vector<Person>& v) {
    for (Person p : v) {
        printf("%d, %f\n", p.age, p.height);
    }
}

int main() {
    vector<Person> v = {
        {11, 167.2},
        {20, 153.4},
        {15, 177.3},
        {18, 180.4},
        {16, 175.8}
    };

    priority_queue<Person> pq1;
    for (Person p : v) {
        pq1.push(p);
    }
    display_pq(pq1);

    priority_queue<Person> pq2(v.begin(), v.end());
    display_pq(pq2);
    
    stable_sort(v.begin(), v.end());
    display_vec(v);

    return 0;
}
