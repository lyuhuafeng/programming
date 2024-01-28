#include <vector>
#include <stack>
using namespace std;

// 站在某栋楼的位置上往两边看，能看到哪些楼，跟这栋楼自己的高度毫无关系。
// 单调严格下降栈，栈顶最低，越往栈底越高，分别是前一个的 prev greater。
//     top 的 prev greater 是 top-1
//     top-1 的 prev greater 是 top-2
//     依次类推
// 当这栋楼作为 new 来到时，没入栈时，站在栈外往栈里看，就是从 top 开始、依次比 top 高的。
// 其实就是栈里所有元素，也就是 st.size()。
// 两个方向都是严格下降，只能两个方向各遍历一次。

vector<int> buildings(const vector<int>& h) {
    int n = h.size();
    vector<int> res(n, 1); // 初始化为 1：先把每栋楼自己先算上

    stack<int> st;
    for (int i = 0; i < n; i++) {
        res[i] += st.size();
        while (!st.empty() && h[i] >= st.top()) {
            st.pop();
        }
        st.push(h[i]);
    }

    // 换个方向遍历，得到往另一个方向看的结果。代码中，只是 i 循环方向变，其余都不变。
    stack<int> su;
    for (int i = n - 1; i >= 0; i--) {
        res[i] += su.size();
        while (!su.empty() && h[i] <= su.top()) {
            su.pop();
        }
        su.push(h[i]);
    }
    return res;
}

// 上面法一，新来的 i 入栈之前，先累加 i 的值。
// 法二，新来的 i 入栈之后，累加 i+1 或 i-1 的值。显然不如法一直观、清晰。收在这里为完整性。
vector<int> buildings2(const vector<int>& h) {
    int n = h.size();
    vector<int> res(n, 1); // 初始化为 1：先把每栋楼自己先算上

    stack<int> st;
    for (int i = 0; i <= n - 1 - 1; i++) {
        while (!st.empty() && h[i] >= st.top()) {
            st.pop();
        }
        st.push(h[i]);
        res[i + 1] += st.size();
    }

    // 换个方向遍历，得到往另一个方向看的结果。代码中，只是 i 循环方向变，其余都不变。
    stack<int> su;
    for (int i = n - 1; i >= 1; i--) {
        while (!su.empty() && h[i] >= su.top()) {
            su.pop();
        }
        su.push(h[i]);
        res[i - 1] += su.size();
    }
    return res;
}

int main() {
    vector<int> heights;
    int h;
    while (scanf("%d", &h) > 0) {
        printf("_read:%d\n", h);
        heights.push_back(h);
    }
    vector<int> res = buildings2(heights);
    for (int i : res) {
        printf("%d ", i);
    }
    // input:  5 3 8 3 2 5
    // output: 3 3 5 4 4 4
    return 0;
}