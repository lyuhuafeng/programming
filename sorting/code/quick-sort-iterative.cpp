#include <utility> // swap()
#include <stack>
using namespace std;

int partition(int a[], int left, int right) {
    int key = a[right];
    int p = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (a[j] <= key) {
            p++;
            swap(a[p], a[j]);
        }
    }
    p++;
    swap(a[p], a[right]);
    return p;
}

// 用 stack 记录每对要排序的 left, right。成对压入，成对弹出。
void qsort(int a[], int left, int right) {
    stack<int> s;
    s.push(left); s.push(right);
    while (!s.empty()) {
        right = s.top(); s.pop();
        left = s.top(); s.pop();
        int pi = partition(a, left, right);
        if (pi - 1 > left) {
            s.push(left); s.push(pi - 1);
        }
        if (pi + 1 < right) {
            s.push(pi + 1); s.push(right);
        }
    }
}

void display(int a[], int left, int right) {
    for (int i = left; i <= right; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[]= { 3, 9, 2, 4, 12, 1, 8, 4, 2 };
    int len = sizeof a / sizeof(int);
    display(a, 0, len - 1);
    qsort(a, 0, len - 1);
    display(a, 0, len - 1);

    return 0;
}