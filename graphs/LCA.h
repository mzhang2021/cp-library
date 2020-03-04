/**
 * Description: Finds the lowest common ancestor of two nodes in a tree.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/LCA/
 * Time: O(n log n) preprocessing, O(1) query
 */

#include "SparseTable.h"

#define MAXN 100000
#define LOG 18

int idx, tm[MAXN], node[2*MAXN], depth[2*MAXN];
vector<int> adj[MAXN];
RMQ<2*MAXN, LOG> rmq;

void dfs(int u, int p, int d) {
    tm[u] = idx;
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
    if (tm[u] > tm[v])
        swap(u, v);
    return node[rmq.query(tm[u], tm[v])];
}

int dist(int u, int v) {
    return depth[tm[u]] + depth[tm[v]] - 2 * depth[tm[lca(u, v)]];
}

void preprocess() {
    idx = 0;
    dfs(0, -1, 0);
    rmq = RMQ<2*MAXN, LOG>(idx, depth);
}
