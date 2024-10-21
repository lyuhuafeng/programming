import java.util.*;

// leet ac 2023.11.02

class Solution {
    void backtrack(List<Integer> track, int[] nums, List<List<Integer>> res) {
        if (track.size() == nums.length) {
            // 注意要用 track 生成新 List 对象，再加入 res
            // 不然加进去的都是同一个 track 对象的引用
            // 等 dfs 结束、回溯到开始状态时，track 里是空的，res 会是一堆空 List
            res.add(new ArrayList<>(track));
            return;
        }
        for (int i : nums) {
            if (track.contains(i)) {
                continue;
            }
            track.add(i); // 前进一步
            backtrack(track, nums, res);
            track.remove(track.size() - 1); // 回退一步
        }
    }
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> track = new ArrayList<>();
        backtrack(track, nums, res);
        return res;
    }
}

class pm {
    public static void main(String[] args) {
        int[] nums = new int[]{1, 2, 3};
        List<List<Integer>> res = new Solution().permute(nums);
        System.out.println(res);
    }
}
