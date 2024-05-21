 1	#include <bits/stdc++.h>
 2	using namespace std;
 3	int n, m, a[201], b[20], visit[105], s1[10050], s2[100501], t;
 4	void dfs(int cnt, int pos, int sum1, int sum2) {
 5	    if (①) {
 6	        s1[++t] = sum1;
 7	        s2[t] = sum2;
 8	        return;
 9	    }
10	    if (②) return;
11	    dfs(③);
12	    dfs(cnt, pos + 1, sum1, sum2);
13	}
14	int main() {
15	    scanf("%d%d", &n, &m);
16	    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
17	    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
18	    dfs(④);
19	    sort(s1 + 1, s1 + t + 1);
20	    sort(s2 + 1, s2 + t + 1);
21	    int i = 1, j = 1;
22	    while (⑤) {
23	        if (s1[i] == s2[j]) {
24	            printf("%d", s1[i]);
25	            return 0;
26	        }
27	        if (s1[1] < s2[j]) i++;
28	        else j++;
29	    }
30	    printf("IMPOSSIBLE");
31	    return 0;
32	}
