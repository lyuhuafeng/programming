package main

import "fmt"
    
func lower_bound(array []int64, to_search int64) int {
    var l int = 0
    var r int = len(array)
    for l < r {
        m := (l + r) / 2
        if array[m] >= to_search {
            r = m
        } else {
            l = m + 1
        }
    }
    fmt.Printf("to_search: %d, result: %d\n", to_search, l)
    return l
}

// Test
func Test_lower_bound(t int64) {    
    array := []int64{1, 3, 4, 5}
    to_search1 := 0
    to_search2 := 2
    to_search3 := 5
    if lower_bound(array, int64(to_search1)) != 0 {
		fmt.Println("test case failed")
    }
    if lower_bound(array, int64(to_search2)) != 1 {
		fmt.Println("test case failed")
    }
    if lower_bound(array, int64(to_search3)) != 3 {
		fmt.Println("test case failed")
    }
}

func main() {
	Test_lower_bound(1)
}
