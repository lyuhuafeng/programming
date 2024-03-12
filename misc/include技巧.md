
`#include "filename"`：把该文件的所有内容全部复制到当前位置。

可将
```cpp
    char *city_list[] = {
        [O]: "肥东县", [1]: "肥西县", [2]: "长丰县", [3]: "庐江县", 
        [4]: "无为县", [5]: "芜湖县", [6]: "繁昌县", [7]: "南陵县"
    };
```
改为：
```cpp
    char *city_list = {
        #include "city_list.txt"
    };
```
