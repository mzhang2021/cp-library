/**
 * Description: Reduces DP problems with a monotonic cost function from O(k * n^2) to O(k * n log n).
 * Source: https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
 * Verification: https://codeforces.com/contest/321/problem/E
 * Time: O(k * n log n)
 */

#define MAXN 100000
#define MAXK 10

long long dp[MAXK][MAXN];

long long cost(int l, int r);

void solve(int k, int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) / 2;
    pair<long long, int> best(LLONG_MAX, -1);
    for (int i=optl; i<=min(mid, optr); i++)
        best = min(best, {dp[k-1][i] + cost(i, mid), i});

    dp[k][mid] = best.first;
    solve(k, l, mid-1, optl, best.second);
    solve(k, mid+1, r, best.second, optr);
}
