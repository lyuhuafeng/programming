
# `B-tree`（B 树）

[reference](https://github.com/wardseptember/notes/blob/master/docs/B树和B+树详解.md)

a B-tree of order m (m 阶 B 树)：
- 每个 node 有最多 m 个 children
- 每个 internal node（非 root，非 leaf）有至少 ⌈m/2⌉ 个 children
- root node 有至少 2 个 children
- 所有 leaves 都在同一层，且不带信息（空指针），通常称为「失败节点」
- non-leaf node，其 children 数量比所含 key 数量多 1
- 所有 leaves 都在同一层，左右子树高度相等，完全平衡。

一个 node 可包含多个 key（元素），可称为「大节点」。目的：放在外存中，减少访问外存的次数。

lookup: 与 BST 的 lookup 相似。区别：从外存调入「大节点」，然后在「大节点」中找。在任何时刻，通常只有「当前节点」在内存中（从外存中调入地），其他节点还放在外存中。

lookup 时间复杂度：从外存调入内存、在内存中查找。后者耗时可忽略不计。前者：node 间的跳转，作为一次外存访问。所以，只需统计查找过程中访问了多少 node。最多，从 root 到 leaf，访问的节点数，就是树的高度 `O(logm(n))`。m 阶、共 n 个节点。

# `2-3 tree`（2-3 树）

2-3 树是 B-tree 的特例（a B-tree of order 3）。

3-节点：每个节点，最多有 3 个子节点；每个节点，最多存放两个值。
![pics](pics/2-3-tree-nodes.png)

# `B+ tree`（B+ 树）

B-tree 的变种。更适用于文件索引系统、数据库系统等。

严格说，不属于 tree，因 leaf node 之间有连接。

a B+ tree of m order
- 每个 node 有最多 m 个 children
- 每个 internal node（非 root，非 leaf）有至少 ⌈m/2⌉ 个 children
- root node 有至少 2 个 children
- 所有 leaves 都在同一层，且不带信息（空指针），通常称为「失败节点」<font color="red">???</font>

（以上：同 B-tree）

- non-leaf node，其 children 数量与所含 key 数量相同。<font color=red>存疑，貌似 children 数量也是比 key 数量多 1</font>
- non-leaf node 只作为索引。节点中只含其子树的最大或最小的 keys。
- 倒数第二层节点，包含所有的 keys，节点内部有序，节点之间按升序相连。

（以上：与 B-tree 不同）

# `B* tree`

在 B+ tree 基础上，
- 为「内部节点」也增加指向其 sibling 的指针。使除了 root 的每层节点（内部、leaf）都成为单链表。
- 内部节点，key 个数至少为 `(2/3)*m`，节点的利用率提高（对比 B+ tree 的 `1/2`）

代价：
deletion 操作很复杂。

two-to-three split：使每个节点的 key 数量至少为 `(2/3)*m`。

B-start insertion

用处？

# `B*+ tree`

有这个东西吗？