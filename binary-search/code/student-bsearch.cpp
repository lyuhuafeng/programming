#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

struct student {
    string name;
    int age;
    int grade;
};

bool sort_cmp(const student &s1, const student &s2) {
    return s1.age < s2.age;
}

void display(const vector<student> &v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        printf("%02ld: %s, age:%d, grade:%d\n", it - v.begin(), it->name.c_str(), it->age, it->grade);
    }
    printf("\n\n");
}
void display_it(const vector<student> &v, vector<student>::const_iterator it, int k) {
    printf("k:%d, it:%02ld, name:%s, age:%d, grade:%d\n",
            k, it - v.begin(), it->name.c_str(), it->age, it->grade);
}

// for lower_bound()，三种实现，参数、函数体都完全一样
bool operator<(const student &t, int age) {
    return t.age < age;
}
bool lower_cmp(const student &t, int age) {
    return t.age < age;
}
struct lower_functor_cmp {
    bool operator ()(const student &t, int age) const {
        return t.age < age;
    }
};
// for upper_bound()，三种实现，参数、函数体都完全一样
bool operator<(int age, const student &t) {
    return age < t.age;
}
bool upper_cmp(int age, const student &t) {
    return age < t.age;
}
struct upper_functor_cmp {
    bool operator ()(int age, const student &t) const {
        return age < t.age;
    }
};



int main() {
    vector<student> v = {
        { "agor", 9, 4 },
        { "bige", 10, 5 },
        { "dhan", 11, 6 },
        { "ciong", 11, 5 },
        { "ehouxiong", 12, 5 },
        { "fhouchan", 11, 5 },
        { "guaidan", 8, 4 },
        { "higsmart", 3, 5 },
    };
    stable_sort(v.begin(), v.end(), sort_cmp);
    display(v);

    int k = 11;
    vector<student>::const_iterator it;

    it = lower_bound(v.begin(), v.end(), k, lower_cmp);
    display_it(v, it, k);
    it = lower_bound(v.begin(), v.end(), k);
    display_it(v, it, k);
    it = lower_bound(v.begin(), v.end(), k, lower_functor_cmp());
    display_it(v, it, k);

    it = upper_bound(v.begin(), v.end(), k, upper_cmp);
    display_it(v, it, k);
    it = upper_bound(v.begin(), v.end(), k);
    display_it(v, it, k);
    it = upper_bound(v.begin(), v.end(), k, upper_functor_cmp());
    display_it(v, it, k);

    return 0;
}
