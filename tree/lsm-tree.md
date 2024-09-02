
log-structured merge-tree (LSM tree)

sorted run:
- 数据放在若干个 sorted run 里。一个 sorted run 包括一个或多个数据文件（sstable file）。每个数据文件只能属于一个 sorted run。
- 一个数据文件中的数据，按 key 排序。一个 sorted run 中，数据的 key 不能 overlap。
- 不同 sorted run 中的数据的 key，可能 overlap 或相同。


https://dev.to/creativcoder/what-is-a-lsm-tree-3d75

read amplification,
write amplification,
space amplification: 主要指过期的、删除的数据，但仍然还占用存储空间


memtable

sstable (sorted string table)
L0: 是 memtable 直接 dump 得到的，有多个文件；不同文件可能含有重复的 key
L1 及以下：不同文件不能含有重复的 key

见手写笔记


Classically, LSM-trees support two merging policies: leveling and tiering. In leveling, each level may have at most one run, and every time a run in Level i − 1 (i ≥ 1) is moved to Level i, it is greedily sort-merged with the run from Level i, if it exists. With tiering, every level must accumulate T runs before they are sort-merged. Recently hybrid compaction policies (e.g., the hybrid compaction as follows) fuse leveling and tiering in a single tree to strike a balance between the read and write throughput based on workload specifications. To amortize data movement, and thus, avoid latency spikes, state-of-the-art LSM-engines organize data into smaller files, and perform compactions at the granularity of files instead of levels. If Level i grows beyond a threshold, a compaction is triggered and one file (or a subset of files) from Level i is chosen to be compacted with files from Level i + 1 that have an overlapping key-range. This process is known as partial compaction.

传统上，lsm tree 支持两种 merging policy: leveling, tiering.

leveling:

full compaction: 每次 compact 相邻两层的全部数据。compact 之后，上层空，下层含两层所有数据。
partial compaction:


more complex example is RocksDB which applies 1-leveling (tiering for level 1 and leveling for others) (data layout) and compactions are performed at the granularity of one or more files (granularity) according to the level saturation, file staleness and spalce amplification (trigger). RocksDB supports various data movement policy including Least Overlapping, Coldest, Oldest and Tombstone Density.


https://www.alibabacloud.com/blog/an-in-depth-discussion-on-the-lsm-compaction-mechanism_596780

Size-tiered compaction stratey: 优化了 write 操作，write ampl. 较小，但 read/space ampl. 还是较高。例：Scylla

- Memtable periodically flushes data to a sstable.
- 每个 level，可包含多个 ordered run。这些 run 的数据大小尽量接近。
- 某 level 的数据量达到限额，则该 level 的所有 run 合并，成为 next level 的一个新的 sstable/run。若 next level 新增 sstable/run 后也超过限额，则也合并…… （也有说 level 的 run 数量达到 T 后才开始合并）

Leveled compaction strategy: 减少 read/space ampl. 例 levelDB。

- 若干 level，相邻两 level 的数据量的比例是常数 T。T 为常数，则 write ampl. 最小。
- 每个 level，是一个 ordered run，包含若干 sstable 文件。
- 某个 level 的 size 达到限额，则 本 level 与 next level 的 run 进行 merge。

Time windowed compaction strategy - Used for time series databases. In this strategy, a time window is used post which compaction is triggered.

The above are not the only strategies and various systems have developed their own such as the hybrid compaction strategy in ScyllaDB.

hybrid compaction 混合的压缩策略

## rocksDB

https://www.alibabacloud.com/blog/an-in-depth-discussion-on-the-lsm-compaction-mechanism_596780

1. leveled：实际是 leveled 和 tiered 的结合。
从 memtable 到 level 0 是 tired：memtable 写成一个 sstable 文件；L0 有多个 sstable 文件，可能有 overlap。
下面各层是 level policy。每个 level 可有多个 sstable 文件。

2. tired (universal): 没太看明白

3. 混合方式 1：leveled-N

4. 混合方式 2：tiered + leveled


K-D Tree

# MergeTree (by clickhouse)

主键索引、数据分区、数据副本和数据采样等基本能力

ReplacingMergeTree 表引擎具有删除重复数据的特性，
SummingMergeTree 表引擎则会按照排序键自动聚合数据。
如果再给合并树系列的表引擎加上 Replicated 前缀，又会得到一组支持数据副本的表引擎，例如
ReplicatedMergeTree、ReplicatedReplacingMergeTree、ReplicatedSummingMergeTree、ReplicatedAggregatingMergeTree 等等。

https://www.cnblogs.com/traditional/p/15218743.html

CREATE TABLE [IF NOT EXISTS] [db_name.]table_name(
    name1 type [DEFAULT|MATERIALIZED|ALIAS expr],
    name2 type [DEFAULT|MATERIALIZED|ALIAS expr],
    ......
) ENGINE = MergeTree()
[PARTITION BY expr]
ORDER BY expr
[PRIMARY KEY expr]
[SAMPLE BY expr]
[SETTINGS name1=value1, name2=value2, ......]

PARTITON BY：选填，表示分区键，用于指定表数据以何种标准进行分区。分区键既可以是单个字段、也可以通过元组的形式指定多个字段，同时也支持使用列表达式。最常见的莫过于按照时间分区了，数据量非常大的时候可以按照天来分区，一天一个分区，这样查找某一天的数据时直接从指定分区中查找即可。（不要把 partition 和 shard 搞混了。shard 跟集群有关。）

2）ORDER BY：在一个分区内，数据以何种标准进行排序。多个分区之间就没有这种关系。可以是单个或多个字段。
3）PRIMARY KEY：选填，表示主键，声明之后会依次按照主键字段生成一级索引，用于加速表查询。如果不指定，那么主键默认和排序键相同，所以通常直接使用 ORDER BY 代为指定主键。所以一般情况下，在每个分区内，数据与一级索引以相同的规则升序排列（因为数据是按照排序键排列的，而一级索引也是按排序键、也就是主键进行排列的）。和其它关系型数据库不同，MergeTree 允许主键有重复数据（可以通过 ReplacingMergeTree 实现去重）。

4）SAMPLE KEY：选填，抽样表达式。用于声明数据以何种标准进行采样

主键索引(Primary Key)是一张表不可或缺的一部分。若不指定，会导致每次查询都是全表扫描。从而几乎必须指定。


https://developer.aliyun.com/article/1133996
https://erenming.github.io/posts/clickhouse-mergetree/

存储结构：

partition: 分区目录，目录的命名规则为 `${PartiionID}_${MinBlockNum}_${MaxBlockNum}_${Level}`：

- PartiionID：即为分区ID
- MinBlockNum：表示最小数据块编号，后续解释
- MaxBlockNum：表示最大数据块编号，后续解释
- Level：表示该Part被合并过的次数，对于每个新建Part目录而言，其初始值为0，每合并一次则累积加1

目录下有如下文件
- primary.idx：一级索引文件，二进制格式。存放稀疏索引，一张 MergeTree 表只能声明一次一级索引（通过 ORDER BY 或 PRIMARY KEY）。借助稀疏索引，在查询时能排除 primary key 条件范围之外的数据文件，从而减少数据扫描范围，加速查询速度。

merge tree 是列式存储，每个列字段都有自己的文件：
- ${column}.bin 数据文件，二进制，压缩的，默认 lz4 压缩。由多个「数据块」block 组成。
- ${column}.mrk 列字段标记文件，二进制。先通过稀疏索引 primary.idx 找到对应数据的偏移量（.mrk），再通过偏移量直接从 .bin 文件中读数据。
- ${column}.mrk2 如使用了自适应大小的索引间隔，则标记文件会以 .mrk2 命名。
- skp_idx_${column}.idx 与 skp_idx_${column}.mrk：如果在建表语句中声明了二级索引，则会额外生成相应的二级索引与标记文件，它们同样也使用二进制存储。二级索引又称「跳数索引」，目前拥有minmax、set、ngrambf_v1和tokenbf_v1四种类型。这些索引的最终目标与一级稀疏索引相同，都是为了进一步减少所需扫描的数据范围，以加速整个查询过程。

## 写入

每收到写入请求，ClickHouse就会生成一个新的Part目录，接着按index_granularity定义的粒度将数据划分，并依次进行处理，生成primary.idx文件，针对每一行生成.mrk和.bin文件。

## 合并
写入结束后，ClickHouse的后台线程会周期性地选择一些Part进行合并，合并后数据依然有序。

在上文中，我们提到的MinBlockNum此时会取各个part中的MinBlockNum最小值，而MaxBlockNum则会取各个part中的MinBlockNum最小值。例如201403_1_1_0和201403_2_2_0合并后，生成的新part目录为201403_1_2_1。

## 查询
查询的过程本质上可以看做是不断缩小数据扫描的过程。当ClickHouse收到查询请求时，其会首先尝试定位到具体的分区，然后扫描所有的part，然后通过part目录中的一级、二级索引定位到标记，再通过标记找到压缩数据块，并将其加载到内存中进行处理。

此外，为了提升查询性能，ClickHouse还是用了vectorized query execution和以及少量runtime code generation技术，从CPU层面提升性能。

# mergetree vs. lsm tree

ClickHouse's MergeTree is based on the Log-Structured Merge-Tree (LSM-Tree) data structure, but they have some differences:
- Data storage: MergeTree writes data directly to the filesystem, while LSM-Trees accumulate writes in memory and batch them before flushing to disk.
- Data manipulation: MergeTree uses a merge process to combine smaller data parts into larger ones, which can affect query performance. LSM-Trees reduce the number of random disk writes by buffering writes in memory, which enhances performance.
- Data insertion: MergeTree is more suitable for inserting data in batches, but it's not ideal for frequently inserting small amounts of rows. LSM-Trees are optimized for write-intensive workloads and are designed to handle a large volume of writes.


https://posthog.com/handbook/engineering/clickhouse/data-storage

