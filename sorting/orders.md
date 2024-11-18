
order theory 序理论

order theory: 处理 binary relation 的数学。

## binary relation

binary relation 的定义：非空集合 X 上的二元关系 R（binary relation R on a nonempty set X）：是 X x X 的一个子集。由一堆 ordered pair 组成。若 `{x,y} ∈ R`，则称「x is in relation to y」，写作 `xRy`。

binary relation 可能有的一些性质：

- reflexivity: xRx 8 x 2 X
- symmetry: xRy implies yRx
- antisymmetric: xRyRx implies that x = y
- asymmetric: if xRy then not yRx
- transitive: xRyRz implies xRy
- complete: xRy or yRx。就是「可比」？
- acyclic: x1Rx2R:::Rxn implies that x1 6= xn

这些性质可用来定义 classes of preference relations。（吕问：啥叫 preference relations？）

## order

order：是一种特殊的 binary relations. (wiki) (吕问：特殊在哪里？)

（quoted from the book）
an ordering is a binary relation on a set of objects.
跟其他 relation 的区别：order 是 transitive 和 anti-symmetric (5 > 3 但 3 不 > 5) 的。（回答了上面的问题：特殊在哪里？）

p2：order relation 有两种：strict 和 non-strict 的。数学之外，strict 更常见。（生活中，说甲比乙高，通常是指「严格」比乙高）。但数学里，通常允许 equality 和 write（吕问：write 是什么意思），所以主要讨论 non-strict order relation。

[这里](https://ncatlab.org/nlab/show/strict+and+non-strict+orders)提到，strict order 又称为 irreflexive order，non-strict order 又称为 reflexive order。


如下 classes of preference relations:
- equivalence relation: reflexive, symmetric and transitive
- preorder: reflexive, transitive
- partial order: reflexive, transitive, antisymmetric
- linear order: a complete partial order （吕问：就是 total order？）
- total order: 吕问：就是 linear order?

## partial order, total order

偏序 partial order（或直接称为 order）: 常用 `≤` 表示
- reflexive: `a ≤ a`
- antisymmetric: 若 `a ≤ b` 且 `b ≤ a`，则 `a = b`（跟上面提到的写法对比：`a < b` 但 反过来 `b < a` 不成立）
- transitive: 若 `a ≤ b` 且 `b ≤ c`，则 `a ≤ c`

全序 total order:
- partial order 的三个性质都满足
- complete: `a ≤ b` 或 `b ≤ a`，二者之一必定成立（吕住：就是「可比」？吕问：但不能都成立？如果这个 or 是逻辑运算，那二者都成立貌似也可以。to check later。）


wiki 上的直观说法

Those orders like the "subset-of" relation for which there exist incomparable elements are called partial orders; 

orders for which every pair of elements is comparable are total orders.


## weak order

weak order 可能指 total preorder 或 strict weak order。(ref: https://ncatlab.org/nlab/show/weak+order)

<!-- quoted from wiki https://en.wikipedia.org/wiki/Weak_ordering -->
weak order 的直观理解：一个集合的 ranking，其中有些元素可以相等(some members may be tied with each other)。

weak order 是 total order (rankings without ties) 的推广，从而被 (strictly) partially ordered sets 和 preorders 推广。(吕注：后半句没看明白)

几种常见的 formalizing weak order 的方式。可公理化（axiomatize）为：
- as strict weak orderings (strictly partially ordered sets in which incomparability is a transitive relation)
- as total preorders (transitive binary relations in which at least one of the two possible relations exists between every pair of elements)
- as ordered partitions (partitions of the elements into disjoint subsets, together with a total order on the subsets)

<!-- end of quote -->

## strict weak order

<!-- quoted from cpp reference  -->
https://en.cppreference.com/w/cpp/named_req/Compare

c++ stl 里所有排序相关的，都用 strict weak order。定义在名为 Compare 的 named requirement 里。
但这里实际提到了两种关系： strict weak ordering relation 和  equivalence relationship

按这里的定义，需要三种性质：
- For all a, comp(a, a) == false. （不 reflexive；注意 partial/total order 都要求 reflexive）
- 若 comp(a, b) == true 则 comp(b, a) == false.（antisymmetric）
- 若 comp(a, b) == true 且 comp(b, c) == true 则 comp(a, c) == true. (transitive)

相等：
- For all a, equiv(a, a) == true. (reflexive)
- 若 equiv(a, b) == true 则 equiv(b, a) == true. (symmetric)
- 若 equiv(a, b) == true 且 equiv(b, c) == true 则 equiv(a, c) == true. (transitive)

<!-- end of quote -->

<!-- quoted from book: the-c++-standard-library-a-tutorial-and-reference-2012.pdf -->

p314-315, set 和 multiset 的 sorting criterion 定义了 strict weak ordering, which 有四个性质（而不是三个）：多了 transitivity of equivalence 这个性质。

- antisymmetric: 若 x < y is true, then y < x is false.
- transitive：If x < y and y < z, then x < z is true.
- irreflexive: x < x is always false.
- transitivity of equivalence: 大致意思：If a is equivalent to b and b is equivalent to c, then a is equivalent to c.
This means that for operator <: If !(a<b) && !(b<a) is true and !(b<c) && !(c<b) is true then !(a<c) && !(c<a) is true.

根据这些性质，the sorting criterion 也用来检查 equivalence: 若 `!(x<y) && !(y<x)`，则认为二者是 duplicates

p331, map 和 multimap，类似 set 和 multiset 的定义，也是 strict weak ordering.

p495, p596，sort() 要求 strict weak ordering

<!-- end of quote -->

## lattice

lattice `['lætɪs]` n. 格子；格状物；[物]点阵

抽象代数中，格（lattice）是一个基于偏序关系(partial order)建立起来的代数结构，是特殊的偏序集(poset)。