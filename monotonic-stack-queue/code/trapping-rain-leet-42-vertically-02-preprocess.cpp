    int trap_working(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        int ans = 0;

        vector<int> lm(n, 0), rm(n, 0);
        // 预处理每个位置左边的最值
        lm[0] = height[0];
        for (int i = 1; i < n; i++) {
            lm[i] = max(height[i], lm[i - 1]);
        }
        // 预处理每个位置右边的最值
        rm[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rm[i] = max(height[i], rm[i + 1]);
        }

        for (int i = 1; i < n - 1; i++) {
            int cur = height[i], l = lm[i], r = rm[i];
            if (l <= cur || r <= cur) {
                continue;
            }
            ans += min(l, r) - cur;
        }
        return ans;
    }
