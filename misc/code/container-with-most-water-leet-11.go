
func maxArea(height []int) int {
    ans := 0
    for l, r := 0, len(height) - 1; l < r; {
        ans = max(ans, min(height[l], height[r]) * (r - l))
        // 移动较低的一边，那条边可能会变高，使矩形高度变大，「有可能」使矩形面积变大；
        // 移动较高的一边，矩形高度不会变大，不可能使矩形面积变大
        if height[l] < height[r] {
            l++
        } else {
            r--
        }
    }
    return ans
}