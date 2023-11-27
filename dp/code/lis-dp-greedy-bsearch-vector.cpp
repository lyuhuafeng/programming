#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;  

void display(int i, char ai, int j, const vector<char>& f) {
    printf("a[%d]=%c j=%d f: ", i, ai, j);
    for (char c : f) {
        printf(" %c", c);
    }
    printf("\n");
}

int main() {  
    // char a[] = {1, 4, 7, 2, 5, 9, 10, 3};
    char a[] = {3, 6, 3, 2, 4, 6, 7, 5, 4, 3};
    int n = sizeof a / sizeof(char);
    for (int i = 0; i < n; i++) { a[i] += '0'; }

    vector<char> f; // f[i]: 长度为 i+1 的 LIS，其最后一个元素值。

    for (int i = 0; i < n; i++) {
        if (f.empty() || a[i] > f.back()) {
            f.push_back(a[i]);
        } else {
            int j = lower_bound(f.begin(), f.end(), a[i]) - f.begin(); // f[] 中第一个 >= a[i] 的
            f[j] = a[i];
        }
    }
    int ans = f.size();
    printf("ans: %d\n", ans);
    return 0;
}
