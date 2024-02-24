# [`901.` 股票价格跨度](https://leetcode.cn/problems/online-stock-span/)

求每个元素的 previous greater 的位置 +1。本题有意思之处在于，每次输入一个元素，同时需求出该元素的 previous greater 的位置。

需要把原来的算法「分布化」。`next()` 的代码就是 for 循环体里的代码。

# 法一，严格模拟原方法

```cpp
class StockSpanner {
    vector<int> prices;
    stack<int> st;
public:
    StockSpanner() {}

    // prev greater 的位置 +1。新法。单调（严格）下降栈。next() 的代码，就是原来 for 循环体里的代码。
    int next(int price) {
        int i = prices.size(); // 新来的 price 的下标
        while (!st.empty() && prices[st.top()] <= price) {
            st.pop();
        }
        int span = st.empty() ? i + 1: i - (st.top() + 1) + 1;
        st.push(i);
        prices.push_back(price);
        return span;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
```

# 法二

法一严格模拟了原方法，包括用 `prices[]` 数组保存所有输入。其实新来的 price 只与栈顶的若干元素比较，已经被弹出的元素以后就用不到了。所以，可以不用保存所有输入，放入栈中即可。栈中同时保存 price 的下标和值。但无法再像法一那样用 `prices.size()` 得到新来元素的下标，必须增加一个成员变量 i。

```cpp
class StockSpanner {
    stack<pair<int, int>> st; // pair<index, price>
    int i;
public:
    StockSpanner() {
        i = -1; // 初始化为 -1
    }

    // prev greater 的位置 +1。新法。单调（严格）下降栈。
    int next(int price) {
        while (!st.empty() && st.top().second <= price) {
            st.pop();
        }
        i++;
        int span = st.empty() ? i + 1: i - (st.top().first + 1) + 1;
        st.push({i, price});
        return span;
    }
};
```

# 法三

在法二的基础上再优化一下，在栈中一开始放入 `{-1, INT_MAX}`，作为 sentinel，保证栈中永远不空，省去一些判断。i 初始化为 -1，保证「栈空」时计算正确。

注意，这种直接放栈内放入首哨兵的方法，只能在这种「连元素值都放入栈内」的情况下才能用。如果元素值不在栈内，还需要用 `prices[st.top()]` 去取，则栈内只剩首哨兵时，`st.top() = -1`，越界出错。

```cpp
class StockSpanner {
    stack<pair<int, int>> st;
    int i;
public:
    StockSpanner() {
        i = -1;
        st.emplace(i, INT_MAX);
    }

    // prev greater 的位置 +1。新法。单调（严格）下降栈。
    int next(int price) {
        while (st.top().second <= price) {
            st.pop();
        }
        int span = (++i) - (st.top().first + 1) + 1;
        st.push({i, price});
        return span;
    }
};
```
