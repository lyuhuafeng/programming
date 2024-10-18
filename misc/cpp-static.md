# 代码示例

例一

```cpp
    const std::vector<std::string>& MySearch::GetBriefFields() {
        static std::vector<std::string> brief_fields {
            "play_cnt"
        };
        return brief_fields;
    }
```

例二

```cpp
    int& get_static_var() {
        static int x = 42;
        printf("in func: %d\n", x);
        return x;
    }

    int main() {
        int& ref = get_static_var();  // in func: 42
        printf("outside: %d\n", ref); // outside: 42
        ref = 100;
        printf("outside: %d\n", ref); // outside: 100
        ref = get_static_var();       // in func: 100
        printf("outside: %d\n", ref); // outside: 100
        return 0;
    }
```

# static 与 多线程

static 的 local 变量，其初始化发生在 control path 第一次经过其 declaration 时。c++11 之前，可能有 race condition，多个线程都可能认为自己先经过。c++11 之后，确保了其唯一性。所以，有些场景下，可用 static 变量来代替 call_once。单例模式，single global instance。
