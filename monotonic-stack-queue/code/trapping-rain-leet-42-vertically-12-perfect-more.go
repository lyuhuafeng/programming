
// hl[i]: 从左边界统计，到 i 为止，最大的。max{ height[i] }, ∀ i ∈ [0, i]
// hr[i]: 从右边界统计，到 i 为止，最大的。max{ height[i] }, ∀ i ∈ [i, n-1]
func trap(height []int) int {
    n := len(height)
    hl, hr := make([]int, n), make([]int, n)
    maxhl, maxhr := -1, -1
    for i, h := range height {
        j := n - 1 - i
        maxhl, maxhr = max(maxhl, h), max(maxhr, height[j])
        hl[i], hr[j] = maxhl, maxhr
    }

    sum := 0
    // 去掉头尾，因头尾两柱肯定无法盛水
    for i := 1; i <= n - 1 - 1; i++ {
        sum += (min(hl[i], hr[i]) - height[i]) * 1
    }
    return sum
}

// 最佳方法，比上法更简单点
func trap_best(height []int) int {
    n := len(height)
    hl, hr := make([]int, n), make([]int, n)
    hl[0], hr[n - 1] = height[0], height[n - 1]
    for i := 1; i <= n - 1 - 1; i++ {
        j := n - 1 - i
        hl[i], hr[j] = max(hl[i - 1], height[i]), max(hr[j + 1], height[j])
    }

    sum := 0
    // 去掉头尾，因头尾两柱肯定无法盛水
    for i := 1; i <= n - 1 - 1; i++ {
        sum += (min(hl[i], hr[i]) - height[i]) * 1
    }
    return sum
}