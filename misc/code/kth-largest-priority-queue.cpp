#include <queue>
#include <vector>
using namespace std;

/* 基于堆查找数组中最大的 k 个元素 */
priority_queue<int, vector<int>, greater<int>> 
topk_heap(const vector<int> &a, int k) {
    priority_queue<int, vector<int>, greater<int>> h;
    // 将数组的前 k 个元素入堆
    for (int i = 0; i < k; i++) {
        h.push(a[i]);
    }
    // 从第 k+1 个元素开始，保持堆的长度为 k
    for (int i = k; i < a.size(); i++) {
        // 若当前元素大于堆顶元素，则将堆顶元素出堆、当前元素入堆
        if (a[i] > h.top()) {
            h.pop();
            h.push(a[i]);
        }
    }
    return h;
}

int main() {
    vector<int> a {1, 4, 5, 3, 19, 3};
    int k = 2;
    printf("k: %d\n", k);
    priority_queue<int, vector<int>, greater<int>> pq = topk_heap(a, k);
    printf("k-th largest: %d\n", pq.top());
    printf("top k: ");
    while (!pq.empty()) {
        printf("%d ", pq.top());
        pq.pop();
    }
    printf("\n");
    return 0;
}

