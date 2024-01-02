package main

import (
    "fmt"
)

func maxCoins(nums []int) int {
    var n int = len(nums)
    var v []int = make([]int, n + 2)
    for i := 0; i < n; i++ {
        v[i + 1] = nums[i]
    }
    v[0], v[n + 1] = 1, 1

    dp := make([][]int, n + 2)
    for i := 0; i < n + 2; i++ {
        dp[i] = make([]int, n + 2)
    }

    for i := n; i >= 1; i-- {
        for j := i; j <= n; j++ {
            for k := i; k <= j; k++ {
                sum := dp[i][k - 1] + dp[k + 1][j] + v[i - 1] * v[k] * v[j + 1]
                dp[i][j] = max(dp[i][j], sum) // max() built-in since 1.21 (2023.08.08)
            }
        }
    }
    return dp[1][n]
}

func main() {
    var nums []int = []int{3, 1, 5, 8}
    var res int = maxCoins(nums)
    fmt.Printf("%d\n", res)
}