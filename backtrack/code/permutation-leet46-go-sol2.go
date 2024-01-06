package main

import "fmt"

// 递归解法
// permute(nums) 返回序列 nums[] 的所有排列
// 用递归的方式，依次取出 nums[] 的一个元素 c，剩下的元素组成序列 r。
// 递归调用 permute(r)，得到所有子排列，再跟 c 凑在一起，得到完整排列。
func permute(nums []int) [][]int {
    if len(nums) == 1 {
        return [][]int{nums}
    }

    res := [][]int{}
    for i, c := range nums {
        // 以下三行，相当于 r := nums[0:i] + nums[i+1:]，也就是 nums 序列去掉了第 i 个元素
        r := make([]int, i);
        copy(r, nums[:i]);
        r = append(r, nums[i + 1:]...)
        // 对子序列 r，递归调用 permute(r)，得到所有子排列
        sub_p := permute(r)

        // 遍历所有子排列，跟 c 拼接，得到完整排列
        for _, pi := range sub_p {
            res = append(res, append([]int{c}, pi...))
        }
    }

    return res
}

func main() {
    nums := []int{5, 4, 6, 2}
    res := permute(nums)
    fmt.Println(res)
}

