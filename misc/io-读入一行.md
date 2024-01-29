# 读入一行

普通情况下，`scanf()` 和 `cin` 都是用空白（空格、`\t`、`\n`）分隔，所以无法读入带空格的一整行。

# 法一：用 `scanf()` 读入 `char[]`

```cpp
  char a[256 + 1];
  char c;
  scanf("%[^\n]", a);  // 读入一行，含空格，不含结尾换行符
  scanf("%c", &c);     // 读入后续的换行符 (new line, 10)
```

但若一行长度超过 256，则内存越界，出错。(与 `gets()` 同样的问题)

更好的做法
```cpp
  char a[256 + 1], c;
  scanf("%256[^\n]", a);  // 读入最多256个非'\n'字符
  scanf("%c", &c);        // 读入并扔掉换行符
```

注意，`"%256[^\n]"`，不用加 `s`。如果加了 `s` (`"%256[^\n]s"`)，会在换行符之前停下来，然后期待后面是字符 `'s'`。这是不可能的。

其实还应该根据 `scanf()` 的返回值分别处理。最全面的做法

```cpp
  char a[256 + 1];
  int n = scanf("%256[^\n]", a);
  switch (n) {
    case 1:
      break;
    case 0:
      a[0] = 0;
      break;
    case EOF:
      // 做些错误处理
      break;
  }

  char c;
  scanf("%c", &c);
```

若 `n == 1`，说明读入成功，什么也不用做。

若 `n == 0`，说明什么也没读入，遇到的第一个字符就是换行符。或者是个空行，或者上次读一行后没处理换行符。此时，需要设置 `a[0]` 为 0 以使 a 为空字符串。(我其实认为是 `scanf()` 的bug。)

若 `n == EOF`，说明 stdin 被关闭了，或者其他错误。可能需要做些错误处理。

例，OJ-1038，要求读入 4 行，若读一行后忘记再读入换行符，则后续三次 `scanf()` 什么都读不到。若再忘记设置 `a[0] = 0`，则会奇怪地发现四行读入内容都一样。(其实是因为后三次 `scanf()` 失败，未修改字符串内容。)

或者在格式字符串里再加个 `\n`，也可以把换行符读入但并不使用。

```cpp
  char s[256 + 1];
  int n = scanf("%256[^\n]\n", s);
  // 若 n == 1: 成功。与上面处理一致，这里省略
```

或者在格式字符串里再加个 `%*c`：再读入一个字符（即换行符）但丢弃（`*`的作用）：

```cpp
   char str[256 + 1];
   scanf("%256[^\n]%*c", str);
```

# 法二：使用 `std::getline()` 读入 `std::string`

换行符被读了并扔掉。

```cpp
  #include <iostream>
  #include <string>
  using namespace std;

  string s;
  getline(cin, s);        // 默认遇到 '\n' 停止
  getline(cin, s, '\n');  // 显式指定遇到 '\n' 停止
```

# 法三：用 `std::cin.getline()` 读入 `char[]`

换行符被读了并扔掉。为安全，需要指定最多读入多少字符。

```cpp
  #include <iostream>
  using namespace std;

  char str[20];
  cin.getline(str, 20);        // 默认遇到 '\n' 停止
  cin.getline(str, 20, '\n');  // 显式指定遇到 '\n' 停止
```

# 法四：使用 `gets()` 读入 `char[]`。已被废弃。

```cpp
  char name[100];
  gets(name);
```

换行符被读入并扔掉。

但 `gets()` 不安全，对输入不做边界检查，可能导致 segmentation fault。

例如，上面的代码中，如果输入的一行超出 100 个字符，则出错。

因此，`gets()` 从 c11 开始被废弃了。

# 法五：`fgets()`

将来再说
