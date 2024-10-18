#include <cstdio>
#include <cmath> // sqrt()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        cnt += n / i;
    }
    int m = sqrt((double) n);
    cnt = cnt * 2 - m * m;
    printf("%d\n", cnt);
    return 0;
}
