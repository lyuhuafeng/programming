# cpp sleep

# 法一：std 的 `sleep()`

- C++ 11 标准库提供
- macos, linux
  - macos 上不用 `-std=c++11`，linux 上需要。
- 毫秒 (milliseconds, ms)

```cpp
    #include <chrono>
    #include <thread>
    
    // 4500 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(4500));

    using namespace std::literals;
    std::this_thread::sleep_for(3s);
```

# 法二：`usleep()`

- POSIX 标准
- macos, linux
- 微秒 (microseconds, μs, us)

```cpp
    // unistd 是 unix standard 的缩写
    #include <unistd.h> // 不是 <cunistd>
    
    usleep(5000000); // 5 sec
```

# 法三：`sleep()`

- POSIX 标准，windows 上也有兼容版本
- macos, linux
- 秒 (seconds)

```cpp
    // #include <windows.h>
    #include <unistd.h>

    sleep(5); // 5 sec
```
