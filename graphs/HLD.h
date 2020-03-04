/**
 * Description: Performs path queries and updates on a tree.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Verification: https://acm.timus.ru/problem.aspx?space=1&num=1553
 * Time: O(log^2 n) query and update
 */

#include "SegmentTreeLazy.h"

template<int SZ, bool VAL_IN_EDGES>
struct HLD {
    int n, ti, par[SZ], sz[SZ], depth[SZ], root[SZ], pos[SZ];
    vector<vector<int>> adj;
    SegmentTree<SZ> st;

    HLD(vector<vector<int>> &_adj) : n(_adj.size()), tm(0), adj(_adj) {
        root[0] = 0;
        dfsSz(0, -1, 0);
        dfsHld(0, -1);
    }

    void dfsSz(int u, int p, int d) {
        par[u] = p;
        sz[u] = 1;
        depth[u] = d;
        for (int &v : adj[u])
            if (v != p) {
                dfsSz(v, u, d+1);
                sz[u] += sz[v];
                if (sz[v] > sz[adj[u][0]])
                    swap(v, adj[u][0]);
            }
    }

    void dfsHld(int u, int p) {
        pos[u] = ti++;
        for (int v : adj[u])
            if (v != p) {
                root[v] = (v == adj[u][0] ? root[u] : v);
                dfsHld(v, u);
            }
    }

    template<class B>
    void process(int u, int v, B op) {
        for (; root[u]!=root[v]; u=par[root[u]]) {
            if (depth[root[u]] < depth[root[v]])
                swap(u, v);
            op(pos[root[u]], pos[u]);
        }
        if (depth[u] > depth[v])
            swap(u, v);
        op(pos[u] + VAL_IN_EDGES, pos[v]);
    }

    int query(int u, int v) {
        int ret = 0;
        process(u, v, [this, &ret] (int l, int r) {
            ret += st.query(1, 0, n-1, l, r);
        });
        return ret;
    }

    void update(int u, int v, int val) {
        process(u, v, [this, &val] (int l, int r) {
            st.update(1, 0, n-1, l, r, val);
        });
    }
};
