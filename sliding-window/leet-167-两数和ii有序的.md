# [167. 两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted)

java 代码：

```java
    int[] twoSum(int[] numbers, int target) {
        int i = 0, j = numbers.length - 1;
        while (i < j) {
            if (numbers[i] + numbers[j] == target) {
                return new int[]{i + 1, j + 1};
            } else if (numbers[i] + numbers[j] < target) {
                i++;
            } else {
                j--;
            }
        }
        return new int[]{};
    }
```

c++ 代码：

```cpp
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            int t = numbers[i] + numbers[j];
            if (t == target) {
                return {i + 1, j + 1};
            }
            t < target ? i++ : j--; // 用 t <= target 也行。
        }
        return {-1, -1};
    }
```
