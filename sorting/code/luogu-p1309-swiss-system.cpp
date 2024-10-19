/*
luogu P1309, NOIP 2011 普及组, 瑞士轮
https://www.luogu.com.cn/problem/P1309
https://oj.youdao.com/course/13/71/1#/1/10148

方法巧妙。
每轮比赛的所有胜者放入 win[] 数组，负者放入 lose[] 数组。
win[] 和lose[] 已经是有序的，无需对它们再递归排序，只要把 win[] 和lose[] 合并即可。
这一步需调用标准 merge sort 里的 merge()，耗时 O(n)。
总共 R 轮，再考虑到最开始要排序一次，共 O(nlogn + Rn)。

英语学习：瑞士轮 Swiss-system tournament
tournament n. 锦标赛；比赛；比武
*/

// luogu ac 2024.03.21

#include <algorithm>
#include <cstdio>
using namespace std;

struct player {
    int s;
    int w;
    int id;
};
player a[200005], win[100005], lose[100005];

bool operator<(const player &a, const player &b) {
    if (a.s == b.s) {
        return a.id < b.id;
    }
    return a.s > b.s;
}

void merge(int n) {
    int i = 1, j = 1, k = 1;
    int mid = n / 2;
    while (i <= mid && j <= mid) {
        a[k++] = (win[i] < lose[j]) ? win[i++] : lose[j++];
    }
    while (i <= mid) {
        a[k++] = win[i++];
    }
    while (j <= mid) {
        a[k++] = lose[j++];
    }
    // 这里不用把 t[] 拷到 a[]. win[] 和 lose[] 就是临时的。
}

void sdf(int n) {
    for (int i = 1, m = 1; i <= n; i += 2, m++) {
        if (a[i].w > a[i + 1].w) {
            a[i].s++;
            win[m] = a[i];
            lose[m] = a[i + 1];
        } else {
            a[i + 1].s++;
            win[m] = a[i + 1];
            lose[m] = a[i];
        }
    }
}

int main() {
    int n, r, q;
    scanf("%d%d%d", &n, &r, &q);
    n *= 2;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].s);
        a[i].id = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].w);
    }
    sort(a + 1, a + n + 1);
    while (r--) {
        sdf(n);
        merge(n);
    }
    printf("%d", a[q].id);
    return 0;
}
