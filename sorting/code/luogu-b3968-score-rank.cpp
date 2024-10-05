#include <vector>
#include <algorithm>
#include <tuple>
#include <cstdio>
#include <utility>
using namespace std;

// GESP 2024.03 五级, luogu B3968, 成绩排序
// ac 2024.10.04
// 难点：排名有重复的！分数「相等」的，排名一样！
// 排好序之后，再过一遍以求出排名。若跟前一个分数「相等」，则排名与前一个一样。为此重定义了 == 运算符。

struct scores {
    int id;
    int rank;
    int chinese;
    int math;
    int english;
    int total;
    int cm_sum;
    int cm_max;
};

bool operator<(const scores &a, const scores &b) {
    // 下面这两种比较方法都行。注意，第一种，必须用 make_tuple()，不能用 tie()，否则会报错。
    return make_tuple(-a.total, -a.cm_sum, -a.cm_max) < make_tuple(-b.total, -b.cm_sum, -b.cm_max);
    // return tie(a.total, a.cm_sum, a.cm_max) > tie(b.total, b.cm_sum, b.cm_max);
}
bool order_by_id(const scores &a, const scores &b) {
    return a.id < b.id;
}

bool operator==(const scores &a, const scores &b) {
    return a.total == b.total && a.cm_sum == b.cm_sum && a.cm_max == b.cm_max;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<scores> v;
    for (int i = 1; i <= n; i++) {
        int c, m, e;
        scanf("%d%d%d", &c, &m, &e);
        v.push_back({i, 0, c, m, e, c + m + e, c + m, max(c, m)});
    }

    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        if (i == 0 || !(v[i] == v[i - 1])) {
            v[i].rank = i + 1;
        } else {
            v[i].rank = v[i - 1].rank;
        }
    }
    sort(v.begin(), v.end(), order_by_id);
    for (int i = 0; i < n; i++) {
        printf("%d\n", v[i].rank);
    }

    return 0;
}