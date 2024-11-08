# unspecified behavior

ref: https://en.cppreference.com/w/cpp/language/ub

the behavior of the program varies between implementations, and the conforming implementation is not required to document the effects of each behavior.

For example, order of evaluation, whether identical string literals are distinct, the amount of array allocation overhead, etc.

其行为，各实现不同，但不要求写在文档里。（对比：implemention-specific behavior，各实现不同，但要求必须写在文档里）

### 例：move semantics

经过调用 `std::move()` 的 moved-from object，处在 valid but unspecified 的状态中。

### whether identical string literals are distinct

英语学习：distinct `adj.` 明显的；清晰的；不同的；独特的

The compiler is allowed, but not required, to combine storage for equal or overlapping string literals. That means that identical string literals may or may not compare equal when compared by pointer.

Whether all string literals are distinct (即，存储在 nonoverlapping objects 中) and whether successive evaluations of a string-literal yield the same or a different object is unspecified. ([source](https://timsong-cpp.github.io/cppwp/lex.string#16))

distinctness is unspecified, and same string literal can yield different object. (以前的错误行为：implementation-defined) ([source](https://en.cppreference.com/w/cpp/language/string_literal))

注意，c++ string literals，按[这里的说法](https://en.cppreference.com/w/cpp/language/string_literal)，定义为 `const char[N]`，`const wchar_t[N]` 或 `const char{8,16,32}_t[N]`。但代码里，其实还是用指针的，类似 `const char* p = "abc\0def"` 这种形式。

### `std::less`

找不到记录了。to update later.