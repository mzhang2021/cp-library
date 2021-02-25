/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/LCA.h
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(1) query
 */

#include "../data-structures/RMQ.h"

struct LCA {
    vector<int> pos, depth, path, ret;
    vector<vector<int>> adj;
    RMQ<int> rmq;

    LCA(int n) : pos(n), depth(n), adj(n), rmq({}) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = 0) {
        dfs(r, -1);
        rmq = RMQ<int>(ret);
    }

    void dfs(int u, int p) {
        pos[u] = (int) path.size();
        path.push_back(u);
        ret.push_back(pos[u]);
        for (int v : adj[u])
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                path.push_back(u);
                ret.push_back(pos[u]);
            }
    }

    int lca(int u, int v) {
        if (pos[u] > pos[v])
            swap(u, v);
        return path[rmq.query(pos[u], pos[v])];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
