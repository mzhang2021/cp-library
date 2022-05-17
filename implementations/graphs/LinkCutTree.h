/**
 * Description: Dynamic connectivity for forests. To store aggregates on edges, add fake nodes for edges. Nodes are 1-indexed.
 * Source: https://codeforces.com/blog/entry/75885
 * Verification: https://www.spoj.com/problems/DYNACON1/, https://dmoj.ca/problem/ds5easy
 * Time: O(log n)
 */

#include "../data-structures/SplayTree.h"

int access(int u) {
    int v = u;
    splay(u);
    attach(u, 1, 0);
    while (tr[u].p) {
        v = tr[u].p;
        splay(v);
        attach(v, 1, u);
        splay(u);
    }
    return v;
}

void reroot(int u) {
    access(u);
    tr[u].flip = true;
    push(u);
}

void link(int u, int v) {
    reroot(u);
    tr[u].p = v;
}

void cut(int u, int v) {
    reroot(u);
    access(v);
    tr[v].ch[0] = tr[u].p = 0;
    pull(v);
}

int lca(int u, int v) {
    access(u);
    return access(v);
}

bool same(int u, int v) {
    access(u);
    access(v);
    return tr[u].p;
}
