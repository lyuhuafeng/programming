package main

import "fmt"

func contains(p []int, num int) bool {
    for _, val := range p {
        if val == num {
            return true
        }
    }
    return false
}
func backtrack(nums []int, res *[][]int, p []int) {
    if len(p) == len(nums) {
        *res = append(*res, p)
        return
    }
    for _, num := range nums {
        if ! contains(p, num) {
            backtrack(nums, res, append(p, num))

            /* 下面这三句，不行，还没找到原因 */
            // p = append(p, num)
            // backtrack(nums, res, p)
            // p = p[:len(p) - 1]
        }
    }
}

func permute(nums []int) [][]int {
    var p []int
    var res [][]int
    backtrack(nums, &res, p)
    return res
}


func main() {
    nums := []int{5, 4, 6, 2}
    res := permute(nums)
    fmt.Println(res)
}