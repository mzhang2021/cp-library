/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: https://iq.opengenus.org/binary-lifting-k-th-ancestor-lowest-common-ancestor/
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(log n) query
 */

const int MAXN = 1e5 + 5;
const int LOG = 17;

int n, depth[MAXN], up[MAXN][LOG];
vector<int> adj[MAXN];

void dfs(int u) {
    for (int v : adj[u])
        if (v != up[u][0]) {
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
}

void preprocess() {
    memset(up, -1, sizeof(up));
    dfs(0);

    for (int j=1; 1<<j<=n; j++)
        for (int i=0; i<n; i++)
            if (up[i][j-1] != -1)
                up[i][j] = up[up[i][j-1]][j-1];
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    for (int j=LOG-1; j>=0; j--)
        if (depth[u] - (1 << j) >= depth[v])
            u = up[u][j];

    if (u == v)
        return u;

    for (int j=LOG-1; j>=0; j--)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }

    return up[u][0];
}

int kthAncestor(int u, int k) {
    for (int j=LOG-1; j>=0; j--)
        if (up[u][j] != -1 && 1 << j <= k) {
            u = up[u][j];
            k -= 1 << j;
        }

    if (k > 0)
        return -1;
    return u;
}
