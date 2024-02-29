# [`luogu P1198 [JSOI2008]` 最大数](https://www.luogu.com.cn/problem/P1198)

- [l5, u9, ex2](https://oj.youdao.com/course/37/278/1#/1/14204)

# 法一，单调栈

用单调递减栈，存放 `{data, rlen}`。`data` 是值，`rlen` (range length) 是「从自己开始，包括自己，往后总共 rlen 个数的最大值」。

每次有元素被弹出，说明被弹出的数不够大，新来的更大，新来的更有资格担任「从这里开始，过去若干个数的最大值」的角色。显然，每弹出一个栈顶元素，新来元素的「代表范围」就要把被弹出者的「代表范围」包括进去，即 `i.rlen += st.top().rlen`。另外，`i.rlen` 初值为 1，表示：初来乍到、还没入栈，「代表范围」只有自己这 1 个元素。

要找末尾 L 个数的最大值，就从后往前的每个数的 rlen 值加起来，直到 `>= L`。为此，得用 vector 作 stack。

主要优化，是把「遍历 L 个元素」变成了「遍历若干个 rlen 值」。

例：
```
    5 4 2 3 6 5

    5：入栈：5(1)
    4：入栈：5(1) 4(1)
    2：入栈：5(1) 4(1) 2(1)
    3：弹出 2，3(1 + 1) = 3(2)；5(1) 4(1) 3(2)
    6：依次弹出 3、4、5，6(1 + 1 + 1 + 2) = 6(5)；6(5)
    5：入栈：6(5) 5(1)
```

代码，turing ac，luogu subtask0 ac 但 subtask1 fail。

```cpp
    #include <cstdio>
    #include <vector>
    using namespace std;

    struct Node {
        int data; // 数据
        int rlen; // 从自己开始，包括自己，往后总共 rlen 个数的最大值。range length。 
    };

    int main() {
        int M, D;
        scanf("%d%d", &M, &D);

        vector<Node> st; // 用 vector 做单调栈

        int t = 0;
        while (M--) {
            Node k;
            char op;
            int val;
            scanf(" %c%d", &op, &val);
            
            if (op == 'A') {
                Node k = {(val + t) % D, 1};
                while (st.size() > 0 && st.back().data < k.data) {
                    k.rlen += st.back().rlen;
                    st.pop_back();    
                }
                st.push_back(k);
            } else if (op == 'Q') {
                int tlen = 0; // 各 rlen 的累加和
                int i = st.size();
                while (val > tlen) {
                    i--;
                    tlen += st[i].rlen;
                }
                printf("%d\n", st[i].data);
                t = st[i].data;
            }
        }
        return 0;
    }
```

# 其他方法

- 逆 st 表：https://blog.nowcoder.net/n/0c7d96e13b2f460a9ecad7a9b0e1b03c
- splay：https://juejin.cn/post/7096873563524857892
