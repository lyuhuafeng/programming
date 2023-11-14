#include <cstdio>
using namespace std;

int main() {
    long a, b;
    scanf("%ld%ld", &a, &b);
    while (a != b) {
        if (a > b) {
            a /= 2;
        } else {
            b /= 2;
        }
    }
    printf("%ld\n", a);
    return 0;
}