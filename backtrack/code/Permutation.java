import java.util.*;

class Permutation {
    void backtrack(List<Integer> track, int[] nums, List<List<Integer>> res) {
        if (track.size() == nums.length) {
            // 注意要用 track 生成新 List 对象，再加入 res
            // 不然加进去的都是同一个 track 对象的引用
            // 等dfs结束、回溯到开始状态时，track 里是空的，res会是一堆空 List
            res.add(new ArrayList<>(track));
            return;
        }
        for (int i = 0; i < nums.length; i++) {
            if (track.contains(nums[i])) {
                continue;
            }
            track.add(nums[i]); // 前进一步
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
        List<List<Integer>> res = new Permutation().permute(nums);
        System.out.println(res);
    }
}
