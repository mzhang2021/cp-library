/**
 * Description: Persistent DSU that allows "undoing" added edges.
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/UnionFindRollback.h
 * Verification: https://www.codechef.com/problems/GERALD07
 * Time: O(log n)
 */

struct DSU {
    vector<int> par, sz, stk;

    DSU(int n) : par(n), sz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        return u == par[u] ? u : find(par[u]);
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
        stk.push_back(v);
        return true;
    }

    void undo(int t) {
        while ((int) stk.size() > t) {
            int u = stk.back();
            stk.pop_back();
            sz[par[u]] -= sz[u];
            par[u] = u;
        }
    }
};
