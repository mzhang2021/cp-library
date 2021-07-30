/**
 * Description: Performs path queries and updates on a tree.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Verification: https://acm.timus.ru/problem.aspx?space=1&num=1553
 * Time: O(log^2 n) query and update
 */

#include "SegmentTreeLazy.h"

template<bool VAL_IN_EDGES = false>
struct HLD {
    int n, ti;
    vector<int> par, sz, depth, root, pos;
    vector<vector<int>> adj;
    SegmentTree st;

    HLD(int _n) : n(_n), ti(0), par(n, -1), sz(n, 1), depth(n), root(n), pos(n), adj(n), st(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = -1) {
        if (r == -1) {
            for (int u=0; u<n; u++)
                if (par[u] == -1) {
                    dfsSz(u);
                    dfsHld(u);
                }
        } else {
            dfsSz(r);
            dfsHld(r);
        }
    }

    void dfsSz(int u) {
        if (par[u] != -1)
            adj[u].erase(find(adj[u].begin(), adj[u].end(), par[u]));
        for (int &v : adj[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            dfsSz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    }

    void dfsHld(int u) {
        pos[u] = ti++;
        for (int v : adj[u]) {
            root[v] = (v == adj[u][0] ? root[u] : v);
            dfsHld(v);
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
        if (pos[u] + VAL_IN_EDGES <= pos[v])
            op(pos[u] + VAL_IN_EDGES, pos[v]);
    }

    // path
    int query(int u, int v) {
        int ret = 0;
        process(u, v, [this, &ret] (int l, int r) {
            ret += st.query(l, r);
        });
        return ret;
    }

    void update(int u, int v, int val) {
        process(u, v, [this, &val] (int l, int r) {
            st.update(l, r, val);
        });
    }

    // subtree
    int query(int u) {
        return st.query(pos[u] + VAL_IN_EDGES, pos[u] + sz[u] - 1);
    }

    void update(int u, int val) {
        st.update(pos[u] + VAL_IN_EDGES, pos[u] + sz[u] - 1, val);
    }
};
