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

    BinaryLift(int _n) : n(_n), lg(__lg(n - 1) + 1), depth(n), adj(n), up(n, vector<int>(lg, -1)) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = 0) {
        dfs(r);
        for (int j=1; j<lg; j++)
            for (int i=0; i<n; i++)
                if (up[i][j-1] != -1)
                    up[i][j] = up[up[i][j-1]][j-1];
    }

    void dfs(int u) {
        for (int v : adj[u])
            if (v != up[u][0]) {
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                dfs(v);
            }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        for (int j=lg-1; j>=0; j--)
            if (depth[u] - (1 << j) >= depth[v])
                u = up[u][j];
        if (u == v)
            return u;
        for (int j=lg-1; j>=0; j--)
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        return up[u][0];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int kthAnc(int u, int k) {
        if (k > depth[u])
            return -1;
        for (int j=0; j<lg; j++)
            if (k & (1 << j))
                u = up[u][j];
        return u;
    }
};
