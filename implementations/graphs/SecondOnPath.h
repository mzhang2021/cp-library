/**
 * Description: Finds the second node on a path between two nodes in a tree.
 * Source: https://codeforces.com/blog/entry/71567?#comment-559285
 * Verification: self
 * Time: O(n log n) preprocessing, O(1) query
 */

#include "../data-structures/RMQ.h"

struct SecondOnPath {
    int n;
    vector<int> par, in, out, depth;
    vector<array<int, 3>> ret;
    vector<vector<int>> adj;
    RMQ<array<int, 3>> rmq;

    SecondOnPath(int _n) : n(_n), par(n, -1), in(n), out(n), depth(n), adj(n), rmq({}) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = -1) {
        if (r == -1) {
            for (int u=0; u<n; u++)
                if (par[u] == -1)
                    dfs(u);
        } else {
            dfs(r);
        }
        rmq = RMQ<array<int, 3>>(ret);
    }

    void dfs(int u) {
        in[u] = (int) ret.size();
        ret.push_back({depth[u], -in[u], u});
        for (int v : adj[u])
            if (v != par[u]) {
                par[v] = u;
                depth[v] = depth[u] + 1;
                dfs(v);
            }
        out[u] = (int) ret.size();
    }

    bool anc(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int query(int u, int v) {
        assert(u != v);
        if (anc(u, v))
            return rmq.query(in[u] + 1, in[v])[2];
        else
            return par[u];
    }
};
