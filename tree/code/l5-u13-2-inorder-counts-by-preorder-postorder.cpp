#include <string>
#include <iostream>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    long long ans = 1;
    for (int i = 0; i + 1 < a.size(); i++) {
        for (int j = 1; j < b.size(); j++) {
            if (a[i] == b[j] && a[i + 1] == b[j - 1]) {
                ans *= 2;
            }
        }
    }
    cout << ans << endl;
    return 0;
}