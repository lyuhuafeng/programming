#include <string>
#include <iostream>
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

    int k = 8; // age的最大值，本应遍历arr求得，为简化代码，直接赋值

    int count[k + 1];
    fill_n(count, k + 1, 0);
    for (int i = 0; i < n; i++) {
        count[arr[i].age]++; // count[v]: v 出现的次数
    }
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1]; // count[v]: <=v 出现的次数
    }

    cout << "______ count:" << endl;
    for (int i = 0; i <= k; i++) {
        cout << "age: " << i << " count: " << count[i] << endl;
    }

    student output[n];
    for (int i = n - 1; i >= 0; i--) {
        int age = arr[i].age;
        int idx = count[age] - 1;
        output[idx] = arr[i];
        count[age]--;
    }
    output_result("sorted (reversely)", output, n);
    return 0;
}
