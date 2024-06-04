
MySQL 的默认存储引擎 InnoDB 使用 B+ tree 做索引。

普通磁盘（非 SSD）加载数据需要经过队列、寻道、旋转以及传输的这些过程，大概要花费 10ms



https://xiaolincoding.com/mysql/index/why_index_chose_bpuls_tree.html

B+ 树的非叶子节点不存放实际的记录数据，仅存放索引，因此数据量相同的情况下，相比存储即存索引又存记录的 B 树，B+树的非叶子节点可以存放更多的索引，因此 B+ 树可以比 B 树更「矮胖」，查询底层节点的磁盘 I/O次数会更少。






https://www.cnblogs.com/vianzhang/p/7922426.html 此文甚好

系统从磁盘读取数据到内存时是以磁盘块（block）为基本单位的，位于同一个磁盘块中的数据会被一次性读取出来，而不是需要什么取什么。

InnoDB存储引擎中有页（Page）的概念，页是其磁盘管理的最小单位。InnoDB存储引擎中默认每个页的大小为16KB，可通过参数innodb_page_size将页的大小设置为4K、8K、16K，在MySQL中可通过如下命令查看页的大小：

mysql> show variables like 'innodb_page_size';
1
1
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

## 两类索引

clustered index: B+ tree 的 (key, val) 是 db 的 (id, row_data)
根据 id (primary key) 找对应 row data

secondary index: B+ tree 的 (key, val) 是 db 的 (index, id)
根据 索引 找 id (primary key)


