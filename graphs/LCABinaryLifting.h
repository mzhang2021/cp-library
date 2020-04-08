/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: https://iq.opengenus.org/binary-lifting-k-th-ancestor-lowest-common-ancestor/
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(log n) query
 */

#define MAXN 100000
#define LOG 17

int n, depth[MAXN], dp[MAXN][LOG];
vector<int> adj[MAXN];

void dfs(int u, int d) {
    depth[u] = d;
    for (int v : adj[u])
        if (v != dp[u][0]) {
            dp[v][0] = u;
            dfs(v, d + 1);
        }
}

void preprocess() {
    memset(dp, -1, sizeof(dp));
    dfs(0, 0);

    for (int j=1; 1<<j<=n; j++)
        for (int i=0; i<n; i++)
            if (dp[i][j-1] != -1)
                dp[i][j] = dp[dp[i][j-1]][j-1];
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    for (int j=LOG-1; j>=0; j--)
        if (depth[u] - (1 << j) >= depth[v])
            u = dp[u][j];

    if (u == v)
        return u;

    for (int j=LOG-1; j>=0; j--)
        if (dp[u][j] != dp[v][j]) {
            u = dp[u][j];
            v = dp[v][j];
        }

    return dp[u][0];
}

int kthAncestor(int u, int k) {
    for (int j=LOG-1; j>=0; j--)
        if (dp[u][j] != -1 && 1 << j <= k) {
            u = dp[u][j];
            k -= 1 << j;
        }

    if (k > 0)
        return -1;
    return u;
}
