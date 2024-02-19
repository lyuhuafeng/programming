# [`202.` 快乐数](https://leetcode.cn/problems/happy-number/)

快慢指针方法，思路巧妙。

```cpp
    int digit_square_sum(int n) {
        int sum = 0;
        while (n != 0) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n, fast = n;
        while (true) {
            slow = digit_square_sum(slow);
            fast = digit_square_sum(digit_square_sum(fast));
            if (fast == 1) {
                return true; // 到终点了
            }
            if (slow == fast) {
                return false; // 有环
            }
        }
        return false; // shouldn't be here. to make compiler happy.
    }
```