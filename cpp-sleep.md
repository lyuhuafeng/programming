# cpp sleep

# 法一，`sleep()`

- C++ 11 标准库提供
- macos, linux
  - macos 上不用 `-std=c++11`，linux 上需要。
- 毫秒 (milliseconds, ms)

```cpp
#include <chrono>
#include <thread>
using namespace std;

int main() {
  cout << "thread started" << endl;
  this_thread::sleep_for(chrono::milliseconds(4500));
  cout << "thread slept for 4500 ms" << endl;
  return 0;
}
```

# 法二，`usleep()`

- POSIX 标准
- macos, linux
- 微秒 (microseconds, μs, us)

```cpp
// unistd 是 unix standard 的缩写
#include <unistd.h> // 不是 <cunistd>
using namespace std;

int main() {
    cout << "will sleep for 5 sec" << endl;
    usleep(5000000);
    cout << "done" << endl;
    return 0;
}
```

# 法三，`sleep()`

- POSIX 标准，windows 上也有兼容版本
- macos, linux。
- 秒 (seconds)

```cpp
// #include <windows.h>
#include <unistd.h>
using namespace std;

int main() {
  cout << "will sleep for 5 sec" << endl;
  sleep(5);
  cout << "done" << endl;
  return 0;
}
```
