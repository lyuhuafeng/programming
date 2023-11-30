# Java 二分搜索

利用
- Arrays.binarySearch(): 适用于 array。
  - 时间复杂度 O(log n)。
- Collections.binarysearch(): 适用于 ArrayList、LinkedList 等。
  - 若被搜索的 list 未实现 RandomAccess interface，则时间复杂度为 O(n) 的遍历 + O(log n) 的比较。

被搜索的 array 需要是有序的。

若 array 中含有 k，则返回其索引（但如果有多个元素值为 k，则不确定返回的是哪个的索引）；否则，返回 `(-插入索引 - 1)`。

“插入索引”，是“第一个大于 k 的位置”。有可能是“最后一个元素之后”。若返回值为 i，则可推出 `“插入索引” = -i - 1`。跟上面公式是对称的。

## 利用 Arrays.binarySearch 实现 lower_bound()、upper_bound()

完整代码: [bsearch.java](bsearch.java)

```java
    import java.util.Arrays;

    int lower_bound(int a[], int k) {
        int i = Arrays.binarySearch(a, k);
        if (i < 0) { // 没找到
            return -i - 1;
        } else { // 找到，不确定是哪个，需左移找到第一个
            while (i > 0) {
                if (a[i - 1] == k) {
                    i--;
                } else {
                    return i;
                }
            }
            return i; // 此时 i=0
        }
    }
    int upper_bound(int a[], int k) {
        int i = Arrays.binarySearch(a, k);
        if (i < 0) { // 没找到
            return -i - 1;
        } else { // 找到，不确定是哪个，需右移找到最后一个
            while (i < a.length) {
                if (a[i] == k) {
                    i++;
                } else {
                    return i;
                }
            }
            return i; // 此时 i=a.length
        }
    }
```

As above we already have discussed that we can operate this algorithm either Arrays.binarysearch() vs Collections.binarysearch(). Arrays.binarysearch() works for arrays which can be of primitive data type also. Collections.binarysearch() works for objects Collections like ArrayList and LinkedList. 


