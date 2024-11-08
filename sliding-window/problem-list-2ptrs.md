

[为什么双指针不会错过正确答案？双指针的本质](https://leetcode.cn/problems/sum-of-square-numbers/solutions/748260/shuang-zhi-zhen-de-ben-zhi-er-wei-ju-zhe-ebn3/)

[以及这个解释，图解，貌似比上面的好点，半个三角形](https://leetcode.cn/problems/container-with-most-water/solutions/94102/on-shuang-zhi-zhen-jie-fa-li-jie-zheng-que-xing-tu/)

[数学证明，貌似更严谨](https://leetcode.cn/problems/container-with-most-water/solutions/1/shuang-zhi-zhen-fa-zheng-que-xing-zheng-ming-by-r3/)

移动指针的安全性：如果一次移动指针，消去的所有 `(i,j)` 对，要么是被计算过，要么是可证明的小于某个已计算过的 S(i,j)，则说这一次指针移动是「安全」的。



- 左右对撞指针：需要两个指针，一个指向开头，一个指向末尾，然后向中间遍历，直到满足条件或者两个指针相遇
- 快慢指针：需要两个指针，开始都指向开头，根据条件不同，快指针走得快，慢指针走的慢，直到满足条件或者快指针走到结尾
- 后序指针：常规指针操作是从前向后便利，对于合并和替换类型题，防止之前的数据被覆盖，双指针需从后向前便利


2ptrs
https://leetcode.cn/problems/minimum-absolute-difference-between-elements-with-constraint/


## 左右指针

- 167. 两数之和 II - 输入有序数组 [题解](leet-167-两数和ii有序的.md)
- 18. 四数之和 [题解](leet-18-四数之和.md)
- 15. 16. 三数之和为 0、三数之和最接近某值 [题解](leet-15-16-三数之和.md)
- 11. 盛最多水的容器 [题解](leet-11-盛最多水的容器.md)
- 42. 接雨水 [双指针法题解，见这个文档的「双指针扫描一次」法](../monotonic-stack-queue/leet-42-接雨水多种方法.md#双指针扫描一次)
- 633. 平方数之和 [题解代码](code/leet-633-sum-of-squares.cpp)
- 240. 搜索二维矩阵 II [代码，两种方法，双指针（理解成 BST）、二分](code/leet-240-search-2d-matrix-ii.cpp)
- 524. 通过删除字母匹配到字典里最长单词 [题解代码](code/leet-524-longest-word-by-deleting.cpp)
- 713. 乘积严格小于 K 的子数组 [代码](code/leet-713-subarray-product-less-than-k.cpp)
- 977. 有序数组的平方 [代码，类似归并](https://leetcode.cn/problems/squares-of-a-sorted-array/submissions/503031908/)
- 88. in-place 合并两个有序数组 [题解，归并变化](https://leetcode.cn/problems/merge-sorted-array/submissions/471274273/)
- 75. 荷兰国旗颜色分类 [题解，类似 partition 过程](leet-75-荷兰国旗颜色分类.md)
- 881. 救生艇 [题解](code/leet-881-boats-to-save.cpp)

## 快慢指针

- 27. 移除值为 val 的元素 [两种题解：快慢指针、左右指针](leet-27-移除元素.md)
- 26. 80. 删除有序数组中的重复项系列 [通解](leet-26-80-删除有序数组中的重复项.md)
- 83. 82. 删除排序链表中的重复元素系列 [链表操作，题解](leet-83-82-删除排序链表中的重复元素.md)

- 283. 移动零 [题解](leet-283-移动〇.md)

- 141. 142. 环形链表系列 [题解](leet-141-142-环形链表.md)
- 161. 相交链表 [代码](https://leetcode.cn/problems/intersection-of-two-linked-lists/submissions/503365899/)
- 876. 链表的中间结点
- 19. 删除链表的倒数第 N 个结点
- 206. 翻转链表; 25. k个一组翻转链表: [题解](leet-206-25-翻转链表-k个一组翻转链表.md)
- 24. 两两交换链表中的节点。可认为是 25 的特例，但这里没用 25 的解法：[代码](https://leetcode.cn/problems/swap-nodes-in-pairs/submissions/475738529/)

- 328. 奇偶链表 [代码](https://leetcode.cn/problems/odd-even-linked-list/submissions/503371882/)
- 203. 移除特定值的链表元素 [代码](https://leetcode.cn/problems/remove-linked-list-elements/submissions/503373893/)
- 21. 合并两个有序链表 [代码](https://leetcode.cn/problems/merge-two-sorted-lists/submissions/475623607/)
- 2. 两数相加. [代码](https://leetcode.cn/problems/add-two-numbers/submissions/475726869/)
- 148. 排序链表（链表的 merge sort）[代码](https://leetcode.cn/problems/sort-list/submissions/475867769/)

- 287. 寻找重复数 [题解，将数组理解为链表的模拟](leet-287-寻找重复数.md)
- 202. 快乐数 [快慢指针解法](leet-202-快乐数.md)

- 345. 反转字符串中的元音字母. [题解](https://leetcode.cn/problems/reverse-vowels-of-a-string/submissions/502688780/)
- 680. 验证回文串 II [题解](https://leetcode.cn/problems/valid-palindrome-ii/submissions/502693587/)


固定间距指针
- 1456. 定长子串中元音的最大数目 [代码](https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/submissions/503089055/)

- 1047. 删除字符串中的所有相邻重复项 [模拟 stack，代码](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/submissions/503099531/)

- 101. 对称二叉树 [递归、递推两种方法](https://leetcode.cn/problems/symmetric-tree/submissions/475784579/)

