# 尾递归 tail recursion

一个递归函数，如果其函数体内做的最后一件事是递归调用自己，就称它为尾递归的。

例如：
```c++
// 尾递归例子
void print(int n) {
    if (n < 0) return;
    printf(" %d", n);
    print(n - 1);
}
```

有迷惑性的例子：
```c++
// 阶乘，普通递归，不是尾递归
unsigned int factorial(unsigned int n) {
    if (n == 0) { return 1 };
    return n * factorial(n - 1);
}
```
`factorial(n - 1)` 的调用是在函数体的最后一行，看起来满足条件。但实际上，`factorial(n - 1)` 的返回值乘以 `n` 才返回；最后一件事是“乘以`n`”而不是`factorial(n - 1)`。所以它不是尾递归的。

改成这样，就是尾递归了。
```c++
// 阶乘，尾递归
long long factorial(long long n, long long a = 1) {
    if (n == 0) {
        return a;
    }
    return factorial(n - 1, a * n);
}
```

普通递归的调用，要等每一级递归都有返回值后，才能得到最终的返回值。

尾递归的调用，最后一级调用的返回值，就是最终返回值。不用等到每一级递归都有返回值。

其调用过程：
```c++
factorial(6, 1)
n == 6: return factorial(5,  (1) * 6 );
n == 5: return factorial(4,  (6) * 5 );
n == 4: return factorial(3,  (6 * 5) * 4);
n == 3: return factorial(2,  (6 * 5 * 4) * 3);
n == 2: return factorial(1,  (6 * 5 * 4 * 3) * 2);
n == 1: return factorial(0,  (6 * 5 * 4 * 3 * 2) * 1);
n == 0: return 6 * 5 * 4 * 3 * 2 * 1;
```
`a` 携带中间结果；每次递归调用都是在更新 `a` 的值。在`n = 0` 时已得到了最终结果，而不用等 `n=1, 2, 3, 4...` 这些调用返回。

## 总结
尾递归和普通递归的区别：
* 形式上：函数内最后一件事是否是对自己的递归调用。
* 实质上：是否要每一级递归调用都返回才能得到最终返回值。