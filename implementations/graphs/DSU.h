/**
 * Description: Maintains and merges disjoint sets.
 * Source: https://cp-algorithms.com/data_structures/disjoint_set_union.html
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=789
 * Time: O(alpha(n)), where alpha(n) is the inverse Ackermann function
 */

template<int SZ>
struct DSU {
    int par[SZ], sz[SZ];

    void init(int n) {
        for (int i=0; i<n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int u) {
        if (u != par[u])
            par[u] = find(par[u]);
        return par[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        if (sz[u] < sz[v])
            swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        return true;
    }
};