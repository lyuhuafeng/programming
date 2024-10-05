
MySQL 的默认存储引擎 InnoDB 使用 B+ tree 做索引。

普通磁盘（非 SSD）加载数据需要经过队列、寻道、旋转以及传输的这些过程，大概要花费 10ms



https://xiaolincoding.com/mysql/index/why_index_chose_bpuls_tree.html

B+ 树的非叶子节点不存放实际的记录数据，仅存放索引，因此数据量相同的情况下，相比存储即存索引又存记录的 B 树，B+树的非叶子节点可以存放更多的索引，因此 B+ 树可以比 B 树更「矮胖」，查询底层节点的磁盘 I/O次数会更少。

https://www.cnblogs.com/vianzhang/p/7922426.html 此文甚好

系统从磁盘读取数据到内存时是以磁盘块（block）为基本单位的，位于同一个磁盘块中的数据会被一次性读取出来，而不是需要什么取什么。

InnoDB存储引擎中有页（Page）的概念，页是其磁盘管理的最小单位。InnoDB存储引擎中默认每个页的大小为16KB，可通过参数 innodb_page_size 将页的大小设置为4K、8K、16K，在MySQL中可通过如下命令查看页的大小：

```sql
mysql> show variables like 'innodb_page_size';
1
```

而系统一个磁盘块的存储空间往往没有这么大，因此InnoDB每次申请磁盘空间时都会是若干地址连续磁盘块来达到页的大小16KB。InnoDB在把磁盘数据读入到磁盘时会以页为基本单位，在查询数据时如果一个页中的每条数据都能有助于定位数据记录的位置，这将会减少磁盘I/O次数，提高查询效率。


- innodb page
- 内存 page
- 磁盘 block


[从数据页的角度看 B+ 树](https://xiaolincoding.com/mysql/index/page.html)

因此，InnoDB 的数据是按「数据页」为单位来读写的，也就是说，当需要读一条记录的时候，并不是将这个记录本身从磁盘读出来，而是以页为单位，将其整体读入内存。

数据库的 I/O 操作的最小单位是页，InnoDB 数据页的默认大小是 16KB，意味着数据库每次读写都是以 16KB 为单位的，一次最少从磁盘中读取 16K 的内容到内存中，一次最少把内存中的 16K 内容刷新到磁盘中。

B+ 树中的每个节点都是一个数据页。（一个 data page 包括多个 disk block？）

每个 disk page 有 next 和 prev 指针，把所有 disk page 连起来，是个 双向链表。让 disk page 之间不是物理上连续的，而是逻辑上连续。

每个 disk page 包含多条 user record（db 的 rows）。多条 record 按「主键」顺序组成单链表。为了检索方便，disk page 还有一个「页目录 page directory」，起到 record 的索引作用，可以直接跳到某条 record。

每个 disk page 的 user record，有两条「虚拟」record，分别表示该 page 的「最小」和「最大」记录，称为 infimum、supermum。「最小」指向实际的最小记录，「最大」被实际的最大记录指向。

所有 record 分成若干组。infinum 单独作为第一组；supermum 不单独成组，而是作为最后一组的最后一条 record。page directory 存储的就是每组最后一条记录的地址偏移量，称为 slot。也就是说，slot 是指向每组最后一条记录的指针；page directory 就是 array of slots。

在 page 里查找记录时，用二分搜索找到对应的 slot，再在该 slot 对应的分组内顺序遍历。

<font color="red">问题：innodb 读 disk，直接读 disk（读一 page），还是读 virtual memory，然后实际由 os 读 disk，操心 paging? </font>好像是前者。

## 两类索引、覆盖索引、索引下推

clustered index 或 primary index: B+ tree 的 `(key, val)` 是 db 的 `(id, row_data)`。

根据 id (primary key) 找对应 row data。

innodb 有且只有一个 clustered index。

secondary index（普通索引、二级索引）: B+ tree 的 `(key, val)` 是 db 的 `(index, id)`。

根据 索引 找 id (primary key)。

若用 secondary index 查询，例如 `select * from order_info where order_status = 'FINISHED'` 这样的：
- 先在 order_status 这棵 B+ tree 的根节点开始，用二分法，逐层向下找，直到找到 `key == 'FINISHED'` 也就是 `order_status = 'FINISHED'` 的叶节点。
- 找到 FINISHED 的起始位置后，扫描所有 FINISHED 的叶节点。这些节点对应的 val 值，就是匹配的记录的 primary ID 值。
- 用上面得到的所有 primary ID，在 db 的 primary index 中查找，找到对应的 row data。（此过程称为「回表 index lookups」）。

回表 index lookup 会降低性能。优化方法：覆盖索引、索引下推

（1）覆盖索引 covering index

把所有想拿的字段（列）都放到索引里，则可直接从 secondary index 的 key 中得到各字段的值。

（2）索引下推 index condition pushdown (ICP)

例 `... where name like '张%' and age = 10 and ismale = 1;`。有个 `(name, age)` 的 secondary index。对比：
- 无 ICP：先根据索引找记录，再根据 where 条件做过滤。根据 name 找到 '张%'，回表得到整条记录，再根据 age 和 ismale 过滤。
- 有 ICP：在查找 secondary index 时，就根据 where 条件做（部分）过滤，有时能大大减少回表次数。根据 name 找到 '张%'，对 key 直接做 `age == 10` 过滤；再对 ismale 回表判断。

## page merging, page splitting

[innodb page merging, page splitting](https://www.percona.com/blog/innodb-page-merging-and-page-splitting/) 及[汉译版](https://blog.csdn.net/weixin_44228698/article/details/119057511)

- 一个 mysql table 对应一个 file
- 一个 file 由 N 个 segment 组成。Each segment is associated with an index.
- 每个 segment 的大小可以一个 extent 为单位增减。每个 extent 固定大小为 1MB。
- 一个 extent 含多个 page。每个 page 固定大小为 16KB。
- 每个 page 就是 B+ tree 的一个 node。
- 每个 page 可包含 2~N 条 record (row)。具体多少，取决于 row size。

MERGE_THRESHOLD，缺省值 50%，对应 B+ tree 定义里「每个 node 至少是 half full 的」。<font color=red>（但实际上这个 threshold 对应的是 page size 而不是 row amount？）</font>

- page merges 在 delete 或 update 时发生。(update 的 row size 变小，导致 page size 低于 threshold)
- page splits 在 Insert 或 Update 时发生，通常导致 page dislocation（逻辑上连续，但物理上不连续，很多时候在不同的 extent 里）

## 

[一篇介绍 b-tree, b+ tree 和数据库索引的文章](https://planetscale.com/blog/btrees-and-database-indexes)