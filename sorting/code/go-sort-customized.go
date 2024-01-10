package main

import "sort"
import "fmt"

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
    sort.Sort(ProductSlice(products[1:])) // 一段排序
    sort.Sort(ProductSlice(products))
    fmt.Println(products)
    fmt.Println("sorted: ", sort.IsSorted(ProductSlice(products)))
    sort.Reverse(ProductSlice(products))
    fmt.Println("sorted: ", sort.IsSorted(ProductSlice(products)))
}
