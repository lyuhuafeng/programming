# c++ stl 排列

## `std::next_permutation(), std::prev_permutation()`

生成全排列的下一个实例
- 范围是 `[first, last)` 左闭右开区间。
- 原地改变 (change in-place)
- 返回值 bool
- 可以指定比较函数
- 通常用 `do … while` 循环。(why?)

字符串

```cpp
    std::string s = "csp";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while (std::next_permutation(s.begin(), s.end()));
    cout << "__ " << s << endl;

// 输出：
cps
csp
pcs
psc
scp
spc         以上输出了全排列的6个实例，到「最大的」一个结束。
__ cps      结束之后，s的值又变成了初始状态
```

数组

```cpp
    int a[] = { 2, 1, 3 };
    int len = sizeof a / sizeof(int);
    do {
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } while (next_permutation(a, a + len));
    printf("__ %d %d %d\n", a[0], a[1], a[2]);

// 输出：
2 1 3
2 3 1
3 1 2      输出到全排列的「最大的」实例停止，没有从头再开始。
3 2 1      因为初始状态不是「最小的」实例。
__ 1 2 3
```

vector

```cpp
    vector<int> v = { 4, 6, 8 };
    do {
        printf("%d %d %d\n", v[0], v[1], v[2]);
    } while (next_permutation(v.begin(), v.end()));
```

数组，逆序，用 prev 而不是 next

```cpp
    int a[] = { 2, 1, 3 };
    int len = sizeof a / sizeof(int);
    sort(a, a + len);
    reverse(a, a + len);
    do {
        printf("%d %d %d\n", a[0], a[1], a[2]);
    } while (prev_permutation(a, a + len));
    printf("__ %d %d %d\n", a[0], a[1], a[2]);

// 输出：
3 2 1
3 1 2
2 3 1
2 1 3
1 3 2
1 2 3
__ 3 2 1
```

`vector<string>`，遍历到开始的那个排列实例

```cpp
    vector<string> w {"seven", "eight", "nine"};
    vector<string> w2 = w;
    do {
        cout << w[0] << " " << w[1] << " " << w[2] << endl;
        next_permutation(w.begin(), w.end());
    } while (w != w2);
```

c-style 字符串，带比较函数

```CPP
    bool cmp(char a, char b) {
        if (tolower(a) != tolower(b)) {
            return tolower(a) < tolower(b);
        } else {
            return a < b;
        }
   }

    char ch[] = "HeLlO";
    sort(ch, ch + strlen(ch), cmp);
    do {
        printf("%s\n", ch);
    } while (next_permutation(ch, ch + strlen(ch), cmp));
```

`vector<string>`，按字符串最后一个字符排序

```cpp
    bool cmp_last(const string &s1, const string &s2) {
        return s1.back() < s2.back();
    }

    vector<string> w { "one", "two", "four" };
    do {
        cout << w[0] << " " << w[1] << " " << w[2] << endl;
    } while (next_permutation(w.begin(), w.end(), cmp_last));
```

## `std::is_permutation()`

看两个序列是否互为排列 (anagram, 变换字母顺序而成的另一词)

```cpp
    vector<int> v1 = { 10, 20, 3, 5 };
    vector<int> v2 = { 20, 10, 5, 3 };
    bool b = is_permutation(v1.begin(), v1.end(), v2.begin());
    
    bool is_equal(int a, int b) {
        return a == b;
    }
    bool b = is_permutation(v1.begin(), v1.end(), v2.begin(), is_equal);
    
    int ar[] = {1, 7, 0, 2};
    int br[] = {0, 7, 2, 1};
    bool b3 = is_permutation(ar, ar + 4, br);
    cout << boolalpha << b3 << endl;
    
    string sa = "SILENT";
    string sb = "LISTEN";
    bool b4 = is_permutation(sa.begin(), sa.end(), sb.begin());
```

找出字符串中某个字符串的排列。

```cpp
    string str = "forxxorfxdofr";
    string pat = "for";
    
    int slen = str.length();
    int plen = pat.length();
    
    for (int i = 0; i <= slen - plen; i++) {
        if (is_permutation(str.begin() + i, str.begin() + i + plen, pat.begin())) {
            cout << i << " " << str.substr(i, plen) << endl;
        }
    }
    
    for (int i = 0; i <= slen - plen; i++) {
        if (is_permutation(pat.begin(), pat.end(), str.begin() + i)) {
            cout << i << " " << str.substr(i, plen) << endl;
        }
    }

// 两种方式都能输出
// 0 for
// 5 orf
// 10 ofr
```

