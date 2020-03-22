/**
 * Description: A divide and conquer technique used on trees by moving through centroids.
 * Source: https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308
 * Verification: https://codeforces.com/contest/342/problem/E
 * Time: O(n log n)
 */

struct CentroidDecomposition {
    vector<int> sub, par;
    vector<bool> visited;
    vector<vector<int>> adj;

    CentroidDecomposition(int n) : sub(n), par(n), visited(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int u = 0, int p = -1) {
        u = centroid(u, p, dfs(u, p));
        par[u] = p;
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v])
                build(v, u);
    }

    int dfs(int u, int p) {
        sub[u] = 1;
        for (int v : adj[u])
            if (v != p && !visited[v])
                sub[u] += dfs(v, u);
        return sub[u];
    }

    int centroid(int u, int p, int sz) {
        for (int v : adj[u])
            if (v != p && !visited[v] && sub[v] > sz / 2)
                return centroid(v, u, sz);
        return u;
    }

    int operator [] (int i) const {
        return par[i];
    }
};
