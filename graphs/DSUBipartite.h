/**
 * Description: Maintains bipartiteness of a graph online.
 * Source: https://cp-algorithms.com/data_structures/disjoint_set_union.html
 * Verification: https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/J
 * Time: O(alpha(n)), where alpha(n) is the inverse Ackermann function
 */

template<int SZ>
struct DSU {
    int par[SZ], sz[SZ];
    bool color[SZ];

    void init(int n) {
        for (int i=0; i<n; i++) {
            par[i] = i;
            sz[i] = 1;
            color[i] = false;
        }
    }

    int find(int u) {
        if (u != par[u]) {
            int v = par[u];
            par[u] = find(v);
            color[u] ^= color[v];
        }
        return par[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool unite(int u, int v) {
        find(u);
        find(v);
        bool x = color[u], y = color[v];
        u = par[u];
        v = par[v];
        if (u == v)
            return x != y;
        if (sz[u] < sz[v])
            swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        color[v] = x ^ y ^ 1;
        return true;
    }
};
