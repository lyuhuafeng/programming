
最常用的自平衡搜索树，是 AVL 和红黑树。

insertion / update 操作后，节点需要 rotate 以恢复树的平衡。

两者的 insert / delete 操作都是 O(log n) 的，但 re-balancing rotation 操作，红黑树是 O(1) 的，而 AVL 是 O(log n)。

所以 map（以及多数 collection 库）使用红黑树，而不是 AVL。包括 C++, Java, .NET 等。

balancing an AVL tree can require O(log n) rotations, whilst a red black tree will take at most two rotations to bring it into balance (though it may have to examine O(log n) nodes to decide where the rotations are necessary)

