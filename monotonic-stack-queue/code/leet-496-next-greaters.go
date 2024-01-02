package main

// nums1 中的每个元素，在 nums2 中找

//// 逆序
func nextGreaterElement_reversed_order(nums1 []int, nums2 []int) []int {
    mp := map[int]int{}
    st := []int{}
    for i := len(nums2) - 1; i >= 0; i-- {
        val := nums2[i]
        for len(st) > 0 && st[len(st) - 1] <= val {
            st = st[:len(st) - 1]
        }
        if len(st) > 0 {
            mp[val] = st[len(st) - 1]
        } else {
            mp[val] = -1
        }
        st = append(st, val)
    }

    res := make([]int, len(nums1))
    for i, val := range nums1 {
        res[i] = mp[val]
    }
    return res
}

//// 正序
func nextGreaterElement(nums1 []int, nums2 []int) []int {
    greaters := make([]int, len(nums2)) // 存下标
    for i, _ := range nums2 {
        greaters[i] = -1
    }
    st := []int{}
    for i := range nums2 {
        // val := nums2[i]
        for len(st) > 0 && nums2[st[len(st) - 1]] < nums2[i] {
            greaters[st[len(st) - 1]] = i
            st = st[:len(st) - 1]
        }
        st = append(st, i)
    }

    mp2 := map[int]int{}
    for i, val := range nums2 {
        mp2[val] = i
    }
    res := make([]int, len(nums1))
    for i, val := range nums1 {
        if gi := greaters[mp2[val]]; gi == -1 {
            res[i] = -1
        } else {
            res[i] = nums2[gi]
        }
    }
    return res
}
