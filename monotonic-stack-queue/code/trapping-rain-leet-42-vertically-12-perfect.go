func trap(height []int) int {
    var maxh int = -1 // 全局最高柱子高度
    li, ri := -1, -1  // 最左、最右的 maxh 的下标
    for i, h := range height {
        if h > maxh {
            maxh = h
            li, ri = i, i // 同时更新最左边、最右边的 maxh 下标
        } else if h == maxh {
            ri = i // 只更新最右边的 maxh 下标
        }
    }

    sum := 0
    maxh_sofar := height[0]
    for i := 1; i < li; i++ {
        if h := height[i]; h < maxh_sofar { // 这个h的赋值，可以覆盖到下面的 else if
            sum += (maxh_sofar - h) * 1
        } else if h > maxh_sofar {
            maxh_sofar = h
        }
    }
    maxh_sofar = height[len(height) - 1]
    for i := len(height) - 1 - 1; i > ri; i-- {
        if h := height[i]; h < maxh_sofar {
            sum += (maxh_sofar - h) * 1
        } else if h > maxh_sofar {
            maxh_sofar = h
        }
    }
    for i := li + 1; i < ri; i++ {
        sum += (maxh - height[i]) * 1
    }
    return sum
}
