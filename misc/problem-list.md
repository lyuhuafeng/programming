
- [179. 最大数](https://leetcode.cn/problems/largest-number/) 看 leet 上我的提交


# 双指针

- [11. 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/)：解法：[`container-with-most-water-leet-11.go`](code/container-with-most-water-leet-11.go)
- [leetcode 42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/) 双指针最简解法：[`trapping-rain-leet-42-vertically-12-perfect-more.go`](monotonic-stack-queue/code/trapping-rain-leet-42-vertically-12-perfect-more.go) [多种解法笔记](monotonic-stack-queue/leet-42-接雨水多种方法.md)

# [byte dance list](https://mp.weixin.qq.com/s/Mczq-QdgQ7UwFlCika09Vg)

- [15. 三数之和](sliding-window/leet-15-16-三数之和.md)
- 3. 无重复字符的最长子串
- [146. LRU 缓存](https://leetcode.cn/problems/lru-cache) [代码](code/leet-146-lru-cache.cpp)、[逻辑更清晰的代码](code/leet-146-lru-cache-better.cpp)（`put()` 代码不同；去掉了 `removeTail()`）
- [460. LFU 缓存](https://leetcode.cn/problems/lfu-cache) [代码](code/leet-460-lfu-cache.cpp)、[代码](code/leet-460-lfu-cache-sol2.cpp)
- [232. 用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks) 
  - 基本思路，一个栈作为 helper 帮助另一个栈：[代码](code/leet-232-queue-by-stacks.cpp)
  - 更好的解法，两个栈协作，分别负责 push 和 pop/peek：[代码](code/leet-232-queue-by-stacks-better.cpp)

- [25. K个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/) 代码：[``]()
- [206. 反转链表](https://leetcode.cn/problems/reverse-linked-list/) 代码：[`leet-206-reverse-linked-list.cpp`](code/leet-206-reverse-linked-list.cpp)
215. 数组中的第K个最大
103. 二叉树的锯齿形层次
200. 岛屿数量
33. 搜索旋转排序数组

# [pdd list](https://mp.weixin.qq.com/s/Mb3D-V_wLPaVqU8fiCWNBw)

- [829. 连续整数求和]()
- [221. 最大正方形]()
- [96. 不同的二叉搜索树]()
- [295. 数据流的中位数](../heap-priority-queue/leet-295-medium-of-stream.md)
- [LCR 146. 螺旋遍历二维数组]()
- [67. 二进制求和]()
- [143. 重排链表]()
- [32. 最长有效括号]()
- [56. 合并区间](https://leetcode.cn/problems/merge-intervals/) 排序后顺序遍历 [merge-intervals-leet-56.cpp](union-find/code/merge-intervals-leet-56.cpp)
- [72. 编辑距离]()

https://mp.weixin.qq.com/s/Rf8dbEGhFNQS4AkXhn6Gew

- [LCR 161. 连续天数的最高销售额](https://leetcode.cn/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/) 或 [53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/): 我已有 dp 法、前缀和法；to do: 分治法

# [didi list](https://mp.weixin.qq.com/s/Mo4Fq0c-Q5e-HsUaY3bq1Q)

- [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

# list

[leetcode 205 道 by 吴师兄](https://mp.weixin.qq.com/s/lEIDrlfOZ5D6GkpP-SFZ6g)





# (blind 75](https://juejin.cn/post/7134304958144479269)

数组：
- [x] 1、两数之和
- [x] 121、买卖股票的最佳时机
- [x] 217、存在重复元素
- [x] 238、除自身以外数组的乘积
- [x] 53、最大子数组和
- [x] 152、乘积最大子数组
- [x] 153、寻找旋转排序数组中的最小值 binary search
- [x] 33、搜索旋转排序数组 binary search
- [x] 15、三数之和 ?
- [x] 11、盛最多水的容器

链表：
- [x] 206、反转链表 ?
- [x] 141、环形链表
- [x] 21、合并两个有序链表 
- [x] 23、合并K个有序链表
- [x] 19、删除链表的倒数第N个结点
- [x] 143、重排链表

字符串：
- [x] 3、无重复字符的最长子串
- [] 424、替换后的最长重复字符
- [x] 76、最小覆盖子串
- [x] 242、有效的字母异位词
- [x] 49、字母异位词分组
- [x] 20、有效的括号
- [x] 125、验证回文串
- [x] 5、最长回文子串
- [x] 647、回文子串 countSubstrings_dp 思路不太好理解；还是看 dp_simple 两种思路
- [] 271、加码解码字符串 vip

图：
- [x] 133、克隆图  看 leet 上我 06.13 的提交，遍历两遍，逻辑清晰
- [x] 207、课程表  拓扑排序
- [x] 417、太平洋大西洋水流问题
- [x] 200、岛屿数量  简单 bfs
- [x] 128、最长连续序列  leet 上我的 _best 题解思路巧妙。注意，不能排序然后二分！因为不是两段的，可能多段！
- [] 269、外星人字典 vip
- [] 261、图验证树 vip
- [] 323、无向图的连通分量 vip

树：
- [x] 104、二叉树的最大深度
- [x] 100、相同的树
- [x] 226、翻转二叉树
- [x] 124、二叉树中的最大路径和 hard
- [x] 102、二叉树的层序遍历
- [x] 297、二叉树的序列化和反序列化，good
- [] 572、另一棵树的子树
- [x] 105、从前序与中序遍历序列构造二叉树
- [x] 98、验证二叉搜索树
- [x] 230、二叉搜索树中第K小的元素
- [x] 235、二叉搜索树的最近公共祖先
- [x] 208、实现Trie（前缀树）
- [] 211、添加与搜索单词-数据结构设计
- [] 212、单词搜索II

区间：
- [x] 57、插入区间
- [x] 56、合并区间
- [x] 435、无重叠区间
- [x] 252、会议室
- [x] 253、会议室II

矩阵
- [] 73、矩阵置零
- [] 54、螺旋矩阵
- [] 48、旋转图像
- [] 79、单词搜索

堆：
- [x] 23、合并K个升序链表
- [x] 347、前K个高频元素
- [x] [295、数据流的中位数](../heap-priority-queue/leet-295-medium-of-stream.md)

bit：
- [] 371、两整数之和
- [] 191、位1的个数
- [] 338、比特位计数
- [] 268、丢失的数字
- [] 190、颠倒二进制位

动态规划：
- [x] 70、爬楼梯
- [x] 322、零钱兑换，完全背包
- [x] 300、最长递增子序列
- [x] 1143、最长公共子序列
- [x] 139、单词拆分
- [x] 377、组合总和IV
- [x] 198、打家劫舍
- [x] 213、打家劫舍II
- [x] 91、解码方法
- [x] 62、不同路径
- [x] 55、跳跃游戏
