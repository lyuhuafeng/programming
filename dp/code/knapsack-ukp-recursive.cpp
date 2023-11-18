#include <cstdio>
#include <vector>
using namespace std;

// int w[] = { 0, 15, 5, 10 };
// int v[] = { 0, 25, 30, 15 };
// int W = 100;

// int w[] = { 0, 1, 3, 4 };
// int v[] = { 0, 15, 20, 30 };
// int W = 4; // 购物车容量

int w[] = { 0, 5, 10, 15 };
int v[] = { 0, 10, 30, 20};
int W = 100; // 购物车容量

int knapsack(int i, int j) {
    if (i == 0 || j == 0) {
        return 0;
    }

    if (j < w[i]) {
        return knapsack(i - 1, j);
    } else {
        return max(knapsack(i, j - w[i]) + v[i], knapsack(i - 1, j));
    }
}

int main() {
    int n = sizeof w / sizeof(int) - 1; // 共多少种物品

    printf("%d\n", knapsack(n, W));
    return 0;
}