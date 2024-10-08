# Trie 前缀树、字典树

一种有序树，用于保存 `(key, value)` 对，其中 key 通常是字符串。

key 不是直接保存在节点中。一个节点对应的 key 值，是从 root 到该节点的路径上，所有字符构成的字符串。

不是所有节点都对应 key 值。所以，通常有个额外字段，标记本节点「是否对应一个 key」，如下面例二。

注意，root 节点不包含字符，是个 dummy 节点。

![pic](pics/trie-demo.png)

本 trie 包括的 key 集合：{"a", "to", "tea", "ted", "ten", "i", "in", "inn"} 。

## 用法一：统计单词数量

[代码](code/trie-example.cpp)

## 用法二：单词是否在词典中、是否为前缀

[leet 208. 实现 Trie (前缀树)](https://leetcode.cn/problems/implement-trie-prefix-tree)

[代码](code/leet-208-trie-impl.cpp)

两者代码基本一样。区别：
- 前者有 count 成员，表示：以我结束的字符串的数量
- 后者有 is_end 成员，表示：以我结束的字符串是否是个合法单词。

这两个，固定 26 个字母，所以用 `trie_node *children[26]` 即可。若不固定，比如汉字，则用 `unordered_map<char, trie_node *>` 更方便。

## 字符串的 top k frequency

被统计的元素是字符串，可用 trie。参考 https://mp.weixin.qq.com/s/mzEuy3XqIja2aqgeT7mKGA

与用法一、二不同的是，字符集是汉字，不确定数量，所以用 map 维护 trie_node 的 children，而不是用数组。

参考[这个解法文档](../misc/top-k-frequent-leet-347.md)

