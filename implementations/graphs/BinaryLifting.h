/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: https://iq.opengenus.org/binary-lifting-k-th-ancestor-lowest-common-ancestor/
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(log n) query
 */

struct BinaryLift {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> adj, up;

    BinaryLift(int _n) : n(_n), lg(__lg(n - 1) + 1), depth(n), adj(n), up(lg, vector<int>(n, -1)) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = -1) {
        if (r == -1) {
            for (int u=0; u<n; u++)
                if (up[0][u] == -1)
                    dfs(u);
        } else {
            dfs(r);
        }
        for (int i=1; i<lg; i++)
            for (int j=0; j<n; j++)
                if (up[i-1][j] != -1)
                    up[i][j] = up[i-1][up[i-1][j]];
    }

    void dfs(int u) {
        for (int v : adj[u])
            if (v != up[0][u]) {
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                dfs(v);
            }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        for (int i=lg-1; i>=0; i--)
            if (depth[u] - (1 << i) >= depth[v])
                u = up[i][u];
        if (u == v)
            return u;
        for (int i=lg-1; i>=0; i--)
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        return up[0][u];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int kthAnc(int u, int k) {
        if (k > depth[u])
            return -1;
        for (int i=0; i<lg; i++)
            if (k >> i & 1)
                u = up[i][u];
        return u;
    }
};
