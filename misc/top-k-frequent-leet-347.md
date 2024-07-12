
[347. 前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements)

top k

- 法一，用 heap，经典方法
- 法二，用类似 insertion sort 的方法，维护一个长度最多为 k 的数组
- 法三，online 流式处理，因为要更新 topk 里已经记录的 freq，故用 set 代替 heap
- 法四，online 流式处理，法一的变种 <font color=red>todo</font>
- trie，参考 https://mp.weixin.qq.com/s/mzEuy3XqIja2aqgeT7mKGA
- 若数据量太多，在磁盘上。需分块，一次读入一部分。若用 heap，要算完所有词的词频才能开始做，可能要把每部分的词频也先存盘，最后合并。若用 set，可按法三处理，不用管中间结果。

流式处理
  - Count-Min Sketch 算法代替 hashmap 
  - Lossy Counting
  - SpaceSaving 原始论文 "Efficient Computation of Frequent and Top-k Elements in Data Streams"
ref:
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/heavy-hitters.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/frequency-estimation.html
  - https://www.cnblogs.com/fxjwind/p/3289221.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/data-stream-sampling.html
  - https://soulmachine.gitbooks.io/system-design/content/cn/bigdata/cardinality-estimation.html

# 法一，用 heap，经典方法

[代码](code/leet-347-top-k-frequency-heap.cpp)

# 法二，用类似 binary insertion sort 的方法，维护一个长度最多为 k 的数组

[代码](code/leet-347-top-k-frequency-insert-sort.cpp)

# 法三，online 流式处理，因为要更新 topk 里已经记录的 freq，故用 set 代替 heap

直观逻辑，[用 struct 的代码](code/leet-347-top-k-frequency-online-struct.cpp)、[用 pair 的代码](code/leet-347-top-k-frequency-online-pair.cpp)

稍微有点不太直观的逻辑，[用 pair 的代码](code/leet-347-top-k-frequency-online-pair-sol2.cpp)

# 用 trie

参考 https://mp.weixin.qq.com/s/mzEuy3XqIja2aqgeT7mKGA

统计姓名，多个字符构成，可用 trie。（若统计数的频率，则无法用 trie）

因字符集不确定，用 map 维护 trie_node 的 children，而不是用数组。

先生成完整的 trie，再 dfs 遍历每个「字符串（姓名）」，找出 top k frequency。

[c++ 代码](code/top-k-frequency-trie.cpp)，[java 代码，待优化](code/top-k-frequency-trie.java)