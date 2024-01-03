// 三个解法，算法都一样，只是 ans[] slice 处理不同
//
// 1. 不指定大小。直接 append。
//   ans := []int{};
//   if i + 1 >= k {
//       ans = append(ans, nums[q[0]])
//   }
//
// 2. 指定大小。给每个 index 赋值。
//   ans := make([]int, len(nums) - k + 1); // 答案
//   if idx := i + 1 - k; idx >= 0 {
//       ans[idx] = nums[q[0]]
//   }
//
// 3. 指定 length、capacity。仍然 append。
//   ans := make([]int, 0, len(nums) - k + 1); // 答案
//   if i + 1 >= k {
//       ans = append(ans, nums[q[0]])
//   }
//

// 求 max value，用单调递降队列

func maxSlidingWindow_sol1(nums []int, k int) []int {
    ans := []int{}; // 答案
    q := []int{}; // 单调队列 (deque)，内放下标
    for i, val := range nums {
        for len(q) > 0 && q[0] + k <= i {
            q = q[1:]
        }
        for len(q) > 0 && nums[q[len(q) - 1]] <= val {
            q = q[:len(q) - 1]
        }
        q = append(q, i)
        if i + 1 >= k {
            ans = append(ans, nums[q[0]])
        }
    }
    return ans
}

func maxSlidingWindow_sol2(nums []int, k int) []int {
    ans := make([]int, len(nums) - k + 1); // 答案
    q := []int{}; // 单调队列 (deque)，内放下标
    for i, val := range nums {
        for len(q) > 0 && q[0] + k <= i {
            q = q[1:]
        }
        for len(q) > 0 && nums[q[len(q) - 1]] <= val {
            q = q[:len(q) - 1]
        }
        q = append(q, i)
        if idx := i + 1 - k; idx >= 0 {
            ans[idx] = nums[q[0]]
        }
    }
    return ans
}

func maxSlidingWindow(nums []int, k int) []int {
    ans := make([]int, 0, len(nums) - k + 1); // 答案
    q := []int{}; // 单调队列 (deque)，内放下标
    for i, val := range nums {
        for len(q) > 0 && q[0] + k <= i {
            q = q[1:]
        }
        for len(q) > 0 && nums[q[len(q) - 1]] <= val {
            q = q[:len(q) - 1]
        }
        q = append(q, i)
        if i + 1 >= k {
            ans = append(ans, nums[q[0]])
        }
    }
    return ans
}
