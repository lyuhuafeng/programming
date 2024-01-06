# go sorting

# sort

`sort` package 中定义，三个函数，用来排序；另三个函数，用来判断序列是否是有序的。注意：
- 函数居然分数据类型；
- 参数（被排序的序列）是 slice；
- 排序是 in-place 的，直接改原序列

```go
    import "sort"

    Float64s(slice)
    Ints(slice)
    Strings(slice)

    Float64sAreSorted(slice)
    IntsAreSorted(slice)
    StringsAreSorted(slice)
```

以 Float64s 为例，参数 floats 是个 slice。
```go
    import "sort”
    floats := []float64 { 279, 48.95, 19.50 } // slice
    sort.Float64s(floats)
```

以 Ints 为例，ints 是个数组，直接用它做参数，则报错；但可以用从它创建的 slice 做参数。
```go
    ints := [...]int { 9, 4, 2, -1, 10} // 数组
    sort.Ints(ints) // 报错：cannot use ints (variable of type [5]int) as []int value ...
    sort.Ints(ints[:]) // 用数组的全部，创建的 slice
    sort.Ints(ints[2:len(ints) - 1]) // 用数组的一部分，创建的 slice
```

以 Strings 为例，不想改原序列，就用 copy 创建新 slice。
```go
    strings := []string { "Kayak", "Lifejacket", "Stadium", "Coat" }
    strs2 := make([]string, len(strings)) // 新 slice
    copy(strs2, strings) // 新 slice 赋值
    sort.Strings(strs2)
```

# search

`sort` package 中，三个函数，用来搜索。注意：
- 参数（被搜索的序列）是已经有序的 slice；
- 如果找到，返回索引；否则，返回可插入的索引。
- 如果有重复元素，返回的索引貌似是第一个元素的索引。

```go
    import "sort"

    SearchInts(slice, val)
    SearchFloat64s(slice, val)
    SearchStrings(slice, val)
    Search(count, testFunc) // 这个还不知道怎么用
```

例
```go
    a := []int { 9, 4, 4, 4, 2, -1, 4, 4, 10}
    sort.Ints(a)
    idx := sort.SearchInts(a, 4)
    is_present := a[idx] == 4 // 4 是否在序列中有
```
