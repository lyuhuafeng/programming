# Trie 前缀树、字典树

用法一：统计单词数量

[代码](code/trie-example.cpp)

用法二：单词是否在词典中、是否为前缀 [leet 208. 实现 Trie (前缀树)](https://leetcode.cn/problems/implement-trie-prefix-tree)

[代码](code/leet-208-trie-impl.cpp)

两者代码基本一样。区别：
- 前者有 count 成员，表示：以我结束的字符串的数量
- 后者有 is_end 成员，表示：以我结束的字符串是否是个合法单词。