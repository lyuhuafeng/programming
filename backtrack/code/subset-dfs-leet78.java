import java.util.*;

class Solution {
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
        dfs(0, nums, t, res);
        return res;
    }
    public static void main(String[] args) {
        int[] nums = new int[]{1, 2, 3};
        List<List<Integer>> res = new Solution().subsets(nums);
        System.out.println(res);
    }
}
