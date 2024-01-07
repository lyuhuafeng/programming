package main

import "fmt"

func backtrack(nums []int, res *[][]int, p []int, used []bool, to_do int) {
    // fmt.Println(p, used, to_do)
    if to_do == len(nums) {
        // fmt.Println("ans:", p)
        p2 := make([]int, len(p))
        copy(p2, p)
        *res = append(*res, p2)
        return
    }
    for i := 0; i < len(nums); i++ {
        if used[i] == false {
            used[i] = true;
            p[to_do] = nums[i];
            backtrack(nums, res, p, used, to_do + 1);
            used[i] = false; // 回溯
        }
    }
}

func permute(nums []int) [][]int {
    var used []bool = make([]bool, len(nums))
    var p []int = make([]int, len(nums))
    var res [][]int
    backtrack(nums, &res, p, used, 0)
    return res
}

func main() {
    nums := []int{5, 4, 6, 2}
    res := permute(nums)
    fmt.Println(res)
}