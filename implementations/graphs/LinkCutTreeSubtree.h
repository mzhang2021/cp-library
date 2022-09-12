/**
 * Description: Dynamic connectivity for forests, supports subtree aggregates. Invertibility is required. Nodes are 1-indexed.
 * Source: https://codeforces.com/blog/entry/67637, https://codeforces.com/blog/entry/75885
 * Verification: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
 * Time: O(log n)
 */

#include "../data-structures/SplayTree.h"

void add(int u, int v) {
    push(v);
    tr[u].vir += tr[v].sum;
}

void rem(int u, int v) {
    push(v);
    tr[u].vir -= tr[v].sum;
}

int access(int u) {
    int v = u;
    splay(u);
    add(u, tr[u].ch[1]);
    attach(u, 1, 0);
    while (tr[u].p) {
        v = tr[u].p;
        splay(v);
        add(v, tr[v].ch[1]);
        rem(v, u);
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
    access(v);
    add(v, u);
    tr[u].p = v;
    pull(v);
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
