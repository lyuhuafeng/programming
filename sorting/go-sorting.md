# go sorting

sort package, slices package

sort 概述
- 基本数据类型，用 `sort.Float64s(slice)`，`sort.Ints(slice)`，`sort.Strings(slice)`
- 自定义数据类型
  - 简单、推荐：用 `sort.Slice(slice, less)`，多提供一个 `less` function
  - 麻烦：`sort.Sort(data Interface)`，还得实现 `sort.Interface` 接口
  - 也还行：`slices.SortFunc(slice, less)`，跟 `sort.Slice()` 差不多。

binary search 概述
- 基本数据类型，用 `sort.Search<Type>s(slice, val)`
- 自定义数据类型，用 `sort.Find()` 或 `sort.Search()`

method 列表
```go
    import "sort"

    // 基本数据类型 slice 排序、判断是否有序
    Float64s(slice)
    Ints(slice)
    Strings(slice)

    Float64sAreSorted(slice)
    IntsAreSorted(slice)
    StringsAreSorted(slice)

    // 根据给定的 less function，对自定义数据类型 slice 排序。
    Slice(slice, less)
    SliceStable(slice, less)
    SliceIsSorted(slice, less)

    // 对 sort.Interface 接口的 slice 排序。
    Sort(data Interface)
    Stable(data Interface)
    IsSorted(data Interface) bool
    // 更推荐 slices.IsSortedFunc

    // 简单 binary search。slice 应该是有序的、升序的。返回 val 所在位置；若无，返回插入位置。
    SearchInts(slice, val)
    SearchFloat64s(slice, val)
    SearchStrings(slice, val)

    // 自定义类型 binary search
    Find(n, cmp)
    Search(n, f)
```

# sort: 基本数据类型的 slice

`sort` package 中定义，三个函数，用来排序；另三个函数，用来判断序列是否是有序的。注意：
- 函数居然分数据类型；
- 参数（被排序的序列）是 slice；
- 排序是 in-place 的，直接改原序列


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

# sort.Slice(): slice of structs, using customer comparator

- `sort.Slice()`
- `sort.SliceStable()`

不是基础类型，需要自定义 comparator function，其参数是待排序的 slice 的两个索引。

```go
    family := []struct {
        Name string
        Age  int
    }{
        {"Alice", 23},
        {"David", 2},
        {"Eve", 2},
        {"Bob", 25},
    }

	// 先定义 comparator，再使用
    cmp_by_age := func(i, j int) bool {
        return family[i].Age < family[j].Age
    }
    sort.Slice(family, cmp_by_age)
    fmt.Println(family)

	// 直接使用匿名函数。匿名函数其实是个 closure。
    sort.SliceStable(family, func(i, j int) bool {
        return family[i].Age < family[j].Age
    })
    fmt.Println(family)
```

# sort.Sort(), sort.Interface: 自定义数据类型的排序

要对某自定义类型（如 Product struct）的 slice 排序，需要先实现名为 `sort.Interface` 的 interface 的三个 method。（这名字起得真不怎么样）

- Len()
- Less(i, j)
- Swap(i, j)

这三个 method 的 receiver，还不能是 `[]Product` 类型，需要自定义一个 alias，如 `type ProductSlice []Product`。

然后，如下 method 用来排序及其他相关操作。

- sort.Sort(p ProductSlice)
- sort.Stable(p ProductSlice)
- sort.IsSorted(p ProductSlice)
- sort.Reversed(p ProductSlice)

示例代码 [`go-sort-customized.go`](code/go-sort-customized.go)。

```go

type Product struct {
    Name string
    Price float64
}

// 自定义 alias，作为 sort.Interface 里三个 method 的 receiver，以及 sort.Sort() 的参数类型
type ProductSlice []Product

// Len(), Less(), Swap() 的 receiver 都是 ProductSlice 类型
func (products ProductSlice) Len() int {
    return len(products)
}
func (products ProductSlice) Less(i, j int) bool {
    return products[i].Price < products[j].Price
}
func (products ProductSlice) Swap(i, j int) {
    products[i], products[j] = products[j], products[i]
}

// sort.Sort() 等参数，需要把 []Product 显式转换成 ProductSlice 类型
func main() {
    products := []Product {
        { "Kayak", 279} ,
        { "Lifejacket", 49.95 },
        { "Soccer Ball",  19.50 },
    }
    sort.Sort(ProductSlice(products[1:]))
    fmt.Println(products)
    fmt.Println("sorted: ", sort.IsSorted(ProductSlice(products)))
    sort.Reverse(ProductSlice(products))
    fmt.Println("sorted: ", sort.IsSorted(ProductSlice(products)))
}
```

# sort.Sort(), sort.Interface: 用其他字段排序

上面例子，用 Price 字段排序。若想用其他字段（Name）排序，可再定义一个 alias，如 `type ProductSliceByName []Product`。

```go
type ProductSlice []Product
type ProductSliceName []Product
```

此种方法，`Less()` 肯定要重新定义，因为用来比较的字段不同了。但 `Len()` 和 `Swap()` 其实只是参数类型遍历，实现完全一样，也要重新定义一遍，比较浪费。

为解决此问题，可使用 type composition，如下所示：

```go
type ProductSliceName struct { ProductSlice } // embeded struct

// Less() 需要重新定义；Len(), Swap() 不用重新定义，会调用 ProductSlice 的
func (p ProductSliceName) Less(i, j int) bool {
    return p.ProductSlice[i].Name < p.ProductSlice[j].Name
}

// 用新的 alias 调用
sort.Sort(ProductSliceName{ p })
```

# sort.Reverse(): 基本数据类型，逆序

`sort.Reverse(data sort.Interface) sort.Interface`，其入参是个 `sort.Interface`，返回值也是个 `sort.Interface`。

```go
	ints := []int{56, 19, 78, 67, 14, 25}
	sort.Sort(sort.Reverse(sort.IntSlice(ints)))
	fmt.Println("reversed:", ints)
```

# sort.Sort(), sort.Interface: 自定义 comparison function 用来比较

to add later

# 用 slices.SortFunc() 排序

跟 `sort.Slice(slice, less)` 用法差不多。

```go
package main

import (
    "cmp"
    "fmt"
    "slices"
)

func main() {
    fruits := []string{"peach", "banana", "kiwi"}

    lenCmp := func(a, b string) int {
        return cmp.Compare(len(a), len(b))
    }

    slices.SortFunc(fruits, lenCmp)
    fmt.Println(fruits)

    type Person struct {
        name string
        age  int
    }

    people := []Person{
        Person{name: "Jax", age: 37},
        Person{name: "TJ", age: 25},
        Person{name: "Alex", age: 72},
    }

    slices.SortFunc(people,
        func(a, b Person) int {
            return cmp.Compare(a.age, b.age)
        })
    fmt.Println(people)
}
```

# 简单 binary search

`sort` package 中，三个函数，用来搜索。注意：
- 参数（被搜索的序列）是已经有序的 slice；
- 如果找到，返回索引；否则，返回可插入的索引。
- 如果有重复元素，返回的索引貌似是第一个元素的索引。

```go
    import "sort"

    SearchInts(slice, val)
    SearchFloat64s(slice, val)
    SearchStrings(slice, val)
```

例
```go
    a := []int { 9, 4, 4, 4, 2, -1, 4, 4, 10}
    sort.Ints(a)
    idx := sort.SearchInts(a, 4)
    is_present := a[idx] == 4 // 4 是否在序列中有
```

# 通用 binary search

```go
func sort.Find(n int, cmp func(int) int) (i int, found bool)
func sort.Search(n int, f func(int) bool) int
```

两者的相同点：
- 对某个序列（array 或 slice），在其下标的左闭右开区间 `[0, n)` 内，查找；

不同点：
- `Find()`: 使 `cmp(i) <= 0` 的最小的 `i`。若无，返回 `n`。`found` 返回收否找到使 `cmp(i) == 0` 的。(序列应为 `ppppp00000nnnnn` (positive, 0, negative) 形式)
- `Search()`: 使 `f(i) == true` 的第一个 `i`。若无，返回 `n`。（序列应为 `fffffttttt` (false, true) 形式）

注意，两者的参数只给了下标的范围 `[0, n)`，`f` 的参数也只是「下标」，都没有给出待搜索的 slice。实际上是在 `f` 里直接访问序列，所以 `f` 或 `cmp` 是个 closure。

例：
```go
    a := []int{1, 3, 5, 7, 7, 7, 9, 11}
    val := 7
    idx := sort.Search(len(a), func(i int) bool { return a[i] >= val })

    if idx < len(a) && a[idx] == val {
        fmt.Printf("Found %d at index %d.\n", val, idx)
    } else {
        fmt.Printf("Not found.\n")
    }
```

```go
    i, found := sort.Find(x.Len(), func(i int) int {
        return strings.Compare(target, x.At(i))
    })
    if found {
        fmt.Printf("found %s at entry %d\n", target, i)
    } else {
        fmt.Printf("%s not found, would insert at %d", target, i)
    }
```
