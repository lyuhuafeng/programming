package main

import "fmt"

func paritition(a []int, left int, right int) int {
	key := a[right]
	p := left - 1
	for j := left; j <= right - 1; j++ {
		if a[j] <= key {
			p++
			a[p], a[j] = a[j], a[p] // swap(a, p, j)
		}
	}
	p++
	a[right], a[p] = a[p], key // swap(a, p, j)
	return p
}

func qsort(a []int, left int, right int) {
	if left >= right {
		return
	}
	p := paritition(a, left, right)
	qsort(a, left, p - 1)
	qsort(a, p + 1, right)
}

func main() {
	list := [...]int{55, 90, 74, 20, 16}
	qsort(list[:], 0, len(list)-1)
	fmt.Println(list)
}