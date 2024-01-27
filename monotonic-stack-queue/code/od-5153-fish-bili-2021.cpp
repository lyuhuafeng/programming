#include <vector>
#include <stack>
#include <algorithm> // max()
#include <cstdio>
using namespace std;

// https://blog.csdn.net/weixin_48157259/article/details/134502718
// https://cloud.tencent.com/developer/article/2117536

struct fish{
    int fish_id, fish_len, t;
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> flen(n);
    // for (int i = 0; i < n; i++) {
    //     scanf("%d", &flen[i]);
    // }
    flen = {4, 3, 2, 3, 2, 1};

    stack<fish> st;
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        printf("new fish: id: %d, len:%d\n", i, flen[i]);
        int t = 0;
        while (!st.empty() && flen[i] > st.top().fish_len){
            t = max(st.top().t, t + 1);
            fish& f = st.top();
            printf("   _pop:  id:%d, len:%d, t:%d. t:%d\n", f.fish_id, f.fish_len, f.t, t);
            st.pop();
        }
        st.push({i, flen[i], t});
        cnt = max(cnt, t);
        printf("   _push: id:%d, len:%d, t:%d. cnt:%d\n", i, flen[i], t, cnt);
    }
    printf("%d\n", cnt);
    return 0;
}
