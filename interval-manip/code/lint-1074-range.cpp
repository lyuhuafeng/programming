#include <set>
#include <cstdio>
#include <iostream>
using namespace std;

struct range {
    int left;
    int right;
};

bool operator<(const range &a, const range &b) {
    return a.left < b.left;
}

class Solution {
private:
    set<range> _ranges;
public:
    void RangeModule() {
        //do some initialization if necessary
    }

    void simply_add(int l, int r) {
        _ranges.insert({l, r});
    }
    
    void addRange(int l, int r) {
        printf("add: %d, %d\n", l, r);
        if (_ranges.empty() || l > _ranges.rbegin()->right || r < _ranges.begin()->left) {
            _ranges.insert({l, r});
            return;
        }
        auto it3 = _ranges.upper_bound({r, 0}); // 第一个 left > r 的
        auto it2 = it3;
        it2--; // 最后一个 left <= r 的
        if (it2->right < l) {
            _ranges.insert({l, r});
            return;
        } // (2)
        int maxr = max(it2->right, r);
        printf("maxr: %d\n", maxr);

        // 左边，找第一个 right >= l 的。它与 l 结合。它作为 erase 的起点。
        // 先找第一个 p. left >= l 的。它的 right 必定 > l
        // p-1.left < l (必定），p-l.right 不一定，要判断一下。
        set<range>::iterator jt1 = _ranges.lower_bound({l, 0}); // 第一个 left >= l 的
        set<range>::iterator jt2 = jt1;
        int minl;
        if (jt1 == _ranges.begin()) {
            minl = min(jt1->left, l);
        } else {
            jt2--;
            // assert(jt2->left <= l)
            if (jt2->right >= l) {
                // jt2 为起点
                minl = jt2->left;
            } else {
                jt2++; // jt1
                minl = l;
            }
        }
        printf("minl: %d\n", minl);

        _ranges.erase(jt2, it3);
        _ranges.insert({minl, maxr});
    }
    
    bool queryRange(int l, int r) {
        set<range>::iterator it = _ranges.upper_bound({l, r}); // 第一个 left > l 的
        if (it == _ranges.begin()) {
            return false;
        }
        it--; // 最后一个 left <= l 的
        return it->right >= r;
    }
    
    void removeRange(int l, int r) {
        if (_ranges.empty() || l >= _ranges.rbegin()->right || r <= _ranges.begin()->left) {
            return;
        }

        auto it1 = _ranges.lower_bound({r, 0}); // 第一个 left >= r 的，绝对不会被删
        auto it2 = it1;
        it2--; // 最后一个 left < r 的，可能全部被删或部分被删
        int n2l = 0, n2r = 0; // n2 初值，空区间
        if (it2->right <= r) {
            // 无 n2
        } else { // left < r < right
            n2l = r, n2r = it2->right; // [r, it2->right) 区间，可能为空
        }

        set<range>::iterator jt1 = _ranges.upper_bound({l, 0}); // 第一个 left > l 的
        set<range>::iterator jt2 = jt1;
        if (jt1 != _ranges.begin()) {
            jt2--; // 最后一个 left <= l 的
        }
        int n1l = 0, n1r = 0;
        if (jt2->right <= l) {
            jt2++; // jt1 起点
            // no left-new element
        } else { // jt2->right > l >= jt2->left
            // jt2 起点
            n1l = jt2->left, n1r = l; // [jt2->left, l) 若相同，则相当于无
        }
        _ranges.erase(jt2, it1);
        if (n1l != n1r) {
            _ranges.insert({n1l, n1r});
        }
        if (n2l != n2r) {
            _ranges.insert({n2l, n2r});
        }
    }

    void display() {
        for (auto &r : _ranges) {
            printf("%d,%d  ", r.left, r.right);
        }
        printf("\n");
    }
};

int main() {
    Solution rm;
    char c;
    int l, r;
    while (scanf(" %c%d%d", &c, &l, &r) != EOF) {
        if (c == 'a') {
            rm.addRange(l, r);
            rm.display();
        } else if (c == 'q') {
            printf("query: %d,%d  ", l, r);
            cout << boolalpha << rm.queryRange(l, r) << endl;
        } else if (c == 'r') {
            rm.removeRange(l, r);
            rm.display();
        }
    }
    return 0;
}
