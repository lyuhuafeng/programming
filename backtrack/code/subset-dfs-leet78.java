import java.util.*;

// leet ac 2023.11.04

class Solution {
    // cur: 将要处理第 cur 个数。从 0 开始算起。
    // 若 cur == n（最大下标 +1），说明所有数都已处理完了，可返回（cur 也不用处理了）
    void dfs(int cur, int[] nums, List<Integer> t, List<List<Integer>> res) {
        if (cur == nums.length) {
            res.add(new ArrayList<>(t));
            return;
        }
        t.add(nums[cur]);
        dfs(cur + 1, nums, t, res);
        t.remove(t.size() - 1);
        dfs(cur + 1, nums, t, res);
    }
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> t = new ArrayList<>();
        dfs(0, nums, t, res); // cur 从 0（第一个数）开始
        return res;
    }
    public static void main(String[] args) {
        int[] nums = new int[]{1, 2, 3};
        List<List<Integer>> res = new Solution().subsets(nums);
        System.out.println(res);
    }
}
