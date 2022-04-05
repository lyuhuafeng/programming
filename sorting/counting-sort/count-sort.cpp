#include <iostream>
using namespace std;

void display(int[], int, string);

void count_sort(int a[], int size) {
  // a[]: 待排序
  // count[]: 计数用;
  // b[]: 排好序后
  int b[100];
  int count[100];

  // 找出最大值 maxn
  int maxn = a[0];
  for (int i = 1; i < size; i++) {
    if (maxn < a[i]) {
      maxn = a[i];
    }
  }

  // 初始化 count[], 下标范围 [0, maxn] 闭区间, 共 maxn + 1 个元素。
  for (int i = 0; i <= maxn; i++) {
    count[i] = 0;
  }

  // 统计每个元素的出现次数. count[i] 就是元素 i 的出现次数
  for (int i = 0; i < size; i++) {
    count[a[i]]++;
  }
  display(count, maxn, "count");

  // 累计计数
  // count[i] 是 <=i 的元素的总出现次数
  for (int i = 1; i <= maxn; i++) {
    count[i] += count[i - 1];
  }
  display(count, maxn, "count");

  // 初始化 b[] 各元素为 0。
  // 只是为了打印中间过程；实际上没必要。
  for (int i = size - 1; i >= 0; i--) {
      b[i] = 0;
  }
  display(b, size, "b");

  // 将 a[] 各元素倒序依次放入 b[] 中合适位置
  for (int i = size - 1; i >= 0; i--) {
    b[count[a[i]] - 1] = a[i];
    display(b, size, "b");
    count[a[i]]--;
  }

  for (int i = 0; i < size; i++) {
    a[i] = b[i];
  }
}

void display(int array[], int size, string s) {
  cout << s << ": ";
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main() {
  int a[] = {4, 2, 2, 8, 3, 3, 1};
  int n = sizeof a / sizeof(int);
  display(a, n, "a");
  count_sort(a, n);
  display(a, n, "a");
}