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

    int Find(int u) {
        if (u != par[u])
            par[u] = Find(par[u]);
        return par[u];
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u != v) {
            if (sz[u] < sz[v])
                swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};
