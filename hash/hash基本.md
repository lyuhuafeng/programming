
## hash function

下面各公式中，m 为桶的数量、哈希表的大小

直接定址：`h(k) = k` 或 `h(k) = a⋅k+b`

乘法 multiplication：`h(k) = floor(m * (A * k 的小数部分))`。常数 A，`0 < A < 1`，Knuth 认为取 0.618... 挺好。

数字分析

平方取中 mid-square: `k^2` 取中间若干位的数字

随机数

折叠 folding: k 分成若干部分，相加，mod m

universal hashing: `h(k) = ((a⋅k+b) mod p) mod m`，p 是个大质数。

除留取余 division：`h(k) = k mod p (p ≤ m)`。p 为质数。



## collision

- 冲突避免 collision avoidance
- 冲突解决 collision resolution

### 开放寻址、开放地址 open addressing (closed hashing)

- linear probing：若 `hash(x) % S` 已被占用，则依次尝试 `(hash(x) + 1) % S`、`(hash(x) + 2) % S`、`(hash(x) + 3) % S` ...
- quadratic probing：`若 hash(x) % S` 已被占用，则依次尝试 `(hash(x) + 1*1) % S`、`(hash(x) + 2*2) % S`、`(hash(x) + 3*3) % S` ...
- double hashing 双重哈希：若 `hash(x) % S` 已被占用，则依次尝试 `(hash(x) + 1 * hash2(x)) % S`、`(hash(x) + 2 * hash2(x)) % S`、`(hash(x) + 3 * hash2(x)) % S` ...

### separate chaining (open hashing)

每个 slot 是个链表

### perfect hashing

设法做到无冲突。类似 seperate chaining，但若有冲突，不是用链表，而是再用一个 hash table。

## misc

load factor
