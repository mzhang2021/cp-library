/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(1) query
 */

#include "../data-structures/RMQ.h"

struct LCA {
    vector<int> in, path, ret, depth;
    vector<vector<int>> adj;
    RMQ<int> rmq;

    LCA(int n) : in(n), depth(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = 0) {
        dfs(r, -1);
        rmq = RMQ<int>(ret);
    }

    void dfs(int u, int p) {
        in[u] = (int) path.size();
        path.push_back(u);
        ret.push_back(in[u]);
        for (int v : adj[u])
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                path.push_back(u);
                ret.push_back(in[u]);
            }
    }

    int lca(int u, int v) {
        if (in[u] > in[v])
            swap(u, v);
        return path[rmq.query(in[u], in[v])];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
