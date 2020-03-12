/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(1) query
 */

#include "SparseTable.h"

#define MAXN 100000
#define LOG 18

int idx, ti[MAXN], node[2*MAXN], depth[2*MAXN];
vector<int> adj[MAXN];
RMQ rmq;

void dfs(int u, int p, int d) {
    ti[u] = idx;
    node[idx] = u;
    depth[idx++] = d;
    for (int v : adj[u])
        if (v != p) {
            dfs(v, u, d + 1);
            node[idx] = u;
            depth[idx++] = d;
        }
}

int lca(int u, int v) {
    if (ti[u] > ti[v])
        swap(u, v);
    return node[rmq.query(ti[u], ti[v])];
}

int dist(int u, int v) {
    return depth[ti[u]] + depth[ti[v]] - 2 * depth[ti[lca(u, v)]];
}

void preprocess() {
    idx = 0;
    dfs(0, -1, 0);
    rmq = RMQ(idx, depth);
}
