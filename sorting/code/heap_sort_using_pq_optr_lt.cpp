#include <cstdio>
#include <queue>
using namespace std;

struct Person {
    int age;
    float height;
};

bool operator<(const Person& p1, const Person& p2) {
    return p1.height < p2.height;
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
    printf("_______before sort\n");
    display_vec(v);

    priority_queue<Person> pq(v.begin(), v.end());
    for (int i = v.size() - 1; i >= 0; --i) {
        v[i] = pq.top(); pq.pop();
    }
    printf("_______after sort\n");
    display_vec(v);

    return 0;
}
