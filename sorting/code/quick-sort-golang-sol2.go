package main

import "fmt"

func paritition(a []int) int {
	right := len(a) - 1
	key := a[right]
	p := -1
	for j, _ := range a {
		if a[j] <= key {
			p++
			a[p], a[j] = a[j], a[p] // swap(a, p, j)
		}
	}
	return p
}

func qsort(a []int) {
	if len(a) <= 1 {
		return
	}
	p := paritition(a)
	qsort(a[:p]) // 右开区间，a[p] 这个元素不被包括
	qsort(a[p + 1:])
}

func main() {
	list := [...]int{55, 90, 74, 20, 16}
	qsort(list[:])
	fmt.Println(list)
}