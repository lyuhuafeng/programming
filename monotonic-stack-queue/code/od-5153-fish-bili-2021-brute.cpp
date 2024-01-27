#include <vector>
#include <cstdio>
using namespace std;

// flen[]: 各鱼的长度
// 模拟，找到每个「尽可能长的严格递减子区间」，只将其最大（最左边）元素保留。
// 复用 flen 空间，用 n、j 记录每轮过后的新序列长度（也就是「最大下标」+1)
int fishes(vector<int> flen) {
    int n = flen.size();
    int rounds = 0;
    while (true) {
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0 || flen[i] >= flen[i - 1]) {
                flen[j++] = flen[i];
            }
        }
        if (n == j) {
            break;
        }
        n = j;
        rounds++;
    }
    return rounds;
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
