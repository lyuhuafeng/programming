// https://www.luogu.com.cn/problem/P7912
// 2024.03.20 所有 case 都通过，无超时

#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

struct block {
    int type;
    list<int> vpos;
};

void display_blocks(const list<block>& v) {
    for (const block& b : v) {
        printf("____ type: %d, ", b.type);
        for (int p : b.vpos) {
            printf(" %d", p);
        }
        printf("\n");
    }
    printf("\n");
}
        
int main() {
    int n;
    scanf("%d", &n);
    list<block> v;
    // int prev = -1;
    // int fruit;
    for (int i = 0, prev = -1; i < n; i++) {
        int fruit;
        scanf("%d", &fruit);
        if (fruit != prev) {
            block b;
            b.type = fruit;
            v.emplace_back(b);
            prev = fruit;
        }
        v.back().vpos.push_back(i + 1);
    }

    while (true) {
        // display_blocks(v);
        for (list<block>::iterator it = v.begin(); it != v.end(); /* it++ */) {
            printf("%d ", it->vpos.front());
            it->vpos.pop_front();
            if (it->vpos.empty()) {
                it = v.erase(it);
            } else {
                it++;
            }
        }
        printf("\n");

        if (v.empty()) {
            break;
        }
        if (v.size() <= 1) {
            continue;
        }
        
        list<block>::iterator jt = v.begin(), it = v.begin();
        it++;
        while (it != v.end()) {
            if (jt->type == it->type) {
                jt->vpos.insert(jt->vpos.end(), it->vpos.begin(), it->vpos.end());
                // for (int pos : it->vpos) {
                //     jt->vpos.push_back(pos);
                // }
                it = v.erase(it);
            } else {
                jt = it++;
            }
        }
    }

    return 0;
}

/*
# cat fruit.in2
20
1 1 1 1 0 0 0 1 1 1 0 0 1 0 1 1 0 0 0 0

# g++ fruit.2.cpp && ./a.out < fruit.in2
____ type: 1,  1 2 3 4
____ type: 0,  5 6 7
____ type: 1,  8 9 10
____ type: 0,  11 12
____ type: 1,  13
____ type: 0,  14
____ type: 1,  15 16
____ type: 0,  17 18 19 20
1 5 8 11 13 14 15 17
____ type: 1,  2 3 4
____ type: 0,  6 7
____ type: 1,  9 10
____ type: 0,  12
____ type: 1,  16
____ type: 0,  18 19 20
2 6 9 12 16 18
____ type: 1,  3 4
____ type: 0,  7
____ type: 1,  10
____ type: 0,  19 20
3 7 10 19
____ type: 1,  4
____ type: 0,  20
4 20
*/