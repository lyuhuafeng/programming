
log-structured merge-tree (LSM tree)

https://dev.to/creativcoder/what-is-a-lsm-tree-3d75

K-D Tree

MergeTree (by clickhouse)

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

