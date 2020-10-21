/**
 * Description: Persistent DSU that allows "undoing" added edges.
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/UnionFindRollback.h
 * Verification: https://www.codechef.com/problems/GERALD07
 * Time: O(log n)
 */

template<int SZ>
struct DSU {
    int par[SZ], sz[SZ];
    vector<int> stk;

    void init(int n) {
        for (int i=0; i<n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
        stk.clear();
    }

    int findRoot(int u) {
        return u == par[u] ? u : findRoot(par[u]);
    }

    bool unite(int u, int v) {
        u = findRoot(u);
        v = findRoot(v);
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
