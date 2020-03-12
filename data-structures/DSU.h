/**
 * Description: Maintains and merges disjoint sets.
 * Source: https://cp-algorithms.com/data_structures/disjoint_set_union.html
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=789
 * Time: O(alpha(n)), where alpha(n) is the inverse Ackermann function
 */

template<int SZ>
struct DSU {
    int parent[SZ], Size[SZ];

    void init(int n) {
        for (int i=0; i<n; i++) {
            parent[i] = i;
            Size[i] = 1;
        }
    }

    int Find(int u) {
        if (u != parent[u])
            parent[u] = Find(parent[u]);
        return parent[u];
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u != v) {
            if (Size[u] < Size[v])
                swap(u, v);
            parent[v] = u;
            Size[u] += Size[v];
        }
    }
};
