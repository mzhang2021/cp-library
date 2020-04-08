/**
 * Description: Reduces DP on intervals with a monotonic cost of splitting array function from O(n^3) to O(n^2).
 * Source: https://apps.topcoder.com/forums/?module=Thread&threadID=697369&start=0&mc=22#1327577
 * Verification: https://www.spoj.com/problems/BRKSTRNG/
 * Time: O(n^2)
 */

#define MAXN 1000

int n, dp[MAXN][MAXN], opt[MAXN][MAXN];

int cost(int l, int r);

void knuth() {
    for (int len=0; len<n; len++)
        for (int i=0; i+len<n; i++) {
            int j = i + len;
            if (len < 2) {
                dp[i][j] = 0;
                opt[i][j] = i;
                continue;
            }

            pair<int, int> best(INT_MAX, -1);
            for (int k=max(opt[i][j-1], i+1); k<=min(opt[i+1][j], j-1); k++)
                best = min(best, {dp[i][k] + dp[k][j] + cost(i, j), k});

            dp[i][j] = best.first;
            opt[i][j] = best.second;
        }
}
