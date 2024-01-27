#include <vector>
#include <cstdio>
using namespace std;

// flen[]: 各鱼的长度
int fishes(vector<int> flen) {
    if (flen.size() <= 1) {
        return 0;
    }
    vector<int> v;
    for (int i = 0; i < flen.size(); i++) {
        if (i == 0 || flen[i] >= flen[i - 1]) {
            v.push_back(flen[i]);
        }
    }
    // 若此轮过后，新序列与原序列长度一样，说明没有互吃，返回 0；否则递归调用。
    return (flen.size() == v.size()) ? 0 : (1 + fishes(v));
}

int main() {
    int n;
    // scanf("%d", &n);
    n = 6;
    vector<int> flen(n);
    // for (int i = 0; i < n; i++) {
    //     scanf("%d", &flen[i]);
    // }
    flen = {4, 3, 2, 3, 2, 1};
    flen = {8, 6, 4, 7, 2, 1};
    int ans = fishes(flen);
    printf("%d\n", ans);
    return 0;
}
