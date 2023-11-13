#include <iostream>
#include <string>
#include <algorithm> // max_element()
using namespace std;

struct student {
    string name;
    int age;
};

void output_result(string msg, student o[], int n) {
    cout << "____ result (" << msg << "):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "age:" << o[i].age << " name:" << o[i].name << endl;
    }
}
int main() {
    student arr[] = {
        {"1.first", 1},
        {"4.first", 4},
        {"1.second", 1},
        {"2.first", 2},
        {"5.first", 5},
        {"2.second", 2},
        {"4.second", 4},
        {"1.third", 1},
        {"8.first", 8}
    };
    int n = sizeof arr / sizeof(student);
    output_result("original", arr, n);

    const student* most_senior = max_element(arr, arr + n, 
            [](const student& a, const student& b) { return a.age < b.age; }); // age的最大值，本应遍历arr求得
    int k = most_senior->age;
    cout << "k:" << k << endl;

    int count[k + 1];
    memset(count, 0, sizeof count);
    for (int i = 0; i < n; i++) {
        count[arr[i].age]++;
    }
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
    }

    cout << "______ count:" << endl;
    for (int i = 0; i <= k; i++) {
        cout << "age: " << i << " count: " << count[i] << endl;
    }

    student output[n];
    for (int i = 0; i < n; i++) {
        int age = arr[i].age;
        int idx = count[age - 1];
        cout << "__ age:" << age << " name:" << arr[i].name << " idx:" << idx << endl;
        output[idx] = arr[i];
        count[age - 1]++;
    }
    output_result("sorted (forwardly)", output, n);
    return 0;
}