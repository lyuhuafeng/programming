

[为什么双指针不会错过正确答案？双指针的本质](https://leetcode.cn/problems/sum-of-square-numbers/solutions/748260/shuang-zhi-zhen-de-ben-zhi-er-wei-ju-zhe-ebn3/)

[以及这个解释，图解，貌似比上面的好点，半个三角形](https://leetcode.cn/problems/container-with-most-water/solutions/94102/on-shuang-zhi-zhen-jie-fa-li-jie-zheng-que-xing-tu/)

[数学证明，貌似更严谨](https://leetcode.cn/problems/container-with-most-water/solutions/1/shuang-zhi-zhen-fa-zheng-que-xing-zheng-ming-by-r3/)

移动指针的安全性：如果一次移动指针，消去的所有 `(i,j)` 对，要么是被计算过，要么是可证明的小于某个已计算过的 S(i,j)，则说这一次指针移动是「安全」的。



- 左右指针：需要两个指针，一个指向开头，一个指向末尾，然后向中间遍历，直到满足条件或者两个指针相遇
- 快慢指针：需要两个指针，开始都指向开头，根据条件不同，快指针走得快，慢指针走的慢，直到满足条件或者快指针走到结尾
- 后序指针：常规指针操作是从前向后便利，对于合并和替换类型题，防止之前的数据被覆盖，双指针需从后向前便利


2ptrs
https://leetcode.cn/problems/minimum-absolute-difference-between-elements-with-constraint/


## 左右指针

- 167. 两数之和 II - 输入有序数组. [题解](leet-167-两数和ii有序的.md)
- 15. 16. 三数之和为 0、三数之和最接近某值 [题解](leet-15-16-三数之和.md)
- 18. 四数之和 [题解](leet-18-四数之和.md)
- 11. 盛最多水的容器 [题解](leet-11-盛最多水的容器.md)
- 42. 接雨水 [双指针法题解，见这个文档的「双指针扫描一次」法](../monotonic-stack-queue/leet-42-接雨水多种方法.md#双指针扫描一次)
- 633. 平方数之和. [题解](https://leetcode.cn/problems/sum-of-square-numbers/submissions/471271654/)
- 240. 搜索二维矩阵 II
- 524. 通过删除字母匹配到字典里最长单词 [题解](leet-524-通过删除字母匹配到字典里最长单词.md)

## 快慢指针

- 27. 移除元素 [两种题解：快慢指针、左右指针](leet-27-移除元素.md)

- 345. 反转字符串中的元音字母. [题解](https://leetcode.cn/problems/reverse-vowels-of-a-string/submissions/502688780/)
- 680. 验证回文串 II [题解](https://leetcode.cn/problems/valid-palindrome-ii/submissions/502693587/)

- 88. 合并两个有序数组 [题解](https://leetcode.cn/problems/merge-sorted-array/submissions/471274273/)
- 141. 环形链表 [题解](https://leetcode.cn/problems/linked-list-cycle/submissions/471274987/) 快慢指针。若 head 指向自己，也算环。开始 `b = a->next`，以免直接 while 结束。


