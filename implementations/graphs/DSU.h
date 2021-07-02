/**
 * Description: Maintains and merges disjoint sets.
 * Source: https://cp-algorithms.com/data_structures/disjoint_set_union.html
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=789
 * Time: O(alpha(n)), where alpha(n) is the inverse Ackermann function
 */

struct DSU {
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
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
