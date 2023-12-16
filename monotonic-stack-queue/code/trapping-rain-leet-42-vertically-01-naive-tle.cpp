    int trap_will_tle(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        for (int i = 1; i < n - 1; i++) {
            int cur = height[i];
            // 获取当前位置的左边最大值
            int l = INT_MIN;
            for (int j = i - 1; j >= 0; j--) {
                l = max(l, height[j]);
            }
            if (l <= cur) {
                continue;
            }

            // 获取当前位置的右边边最大值
            int r = INT_MIN;
            for (int j = i + 1; j < n; j++) {
                r = max(r, height[j]);
            }
            if (r <= cur) {
                continue;
            }
            ans += min(l, r) - cur;
        }
        return ans;
    }
