#include <cstdio>
#include <vector>
#include <algorithm> // min(), max()
using namespace std;

// 用于给每个 bucket 排序
void insertion_sort(vector<float>& bkt) {
    for (int i = 1; i < bkt.size(); ++i) { // 注意从 1 开始。第 0 个元素是「已排序区」的初始态。
        float t = bkt[i];
        int j = i - 1;
        while (j >= 0 && bkt[j] > t) { // 注意 bkt[j] > t 而不是「>=」，为保持稳定性。
            bkt[j + 1] = bkt[j];
            j--;
        }
        bkt[j + 1] = t;
    }
}

// 输入序列长度为 n，桶的数量为 k=n
void bucket_sort(float a[], int n) {
    float minv = a[0], maxv = a[0];
    for (int i = 0; i < n; i++) {
        minv = min(minv, a[i]), maxv = max(maxv, a[i]);
    }
    printf("minv=%f, maxv=%f\n", minv, maxv);
    float gap = maxv - minv;
    int k = n + 1; // bucket 数量，与待排序的 array 长度（实质）相同
    float bkt_size = gap / (k - 1);
    // float bkt_size = gap / k * 1.000001;
    printf("k=%d, gap:%f, bkt_size=%f\n", k, gap, bkt_size);

    vector<float> b[k];
    for (int i = 0; i < n; i++) {
        int bi = int((a[i] - minv) / bkt_size);
        b[bi].push_back(a[i]);
        printf("i:%d, val:%f, idx:%d\n", i, a[i], bi);
    }

    int p = 0;
    // 每个 bucket 排序后就直接放回到 a 中
    for (int i = 0; i < k; i++) {
        insertion_sort(b[i]);
        for (int j = 0; j < b[i].size(); j++) {
            a[p++] = b[i][j];
        }
    }
}

int main() {
    float arr[] = {0.897, 0.896999, 0.8965, 0.896, 0.884, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof arr / sizeof arr[0];
    bucket_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
    return 0;
}
