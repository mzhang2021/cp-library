/**
 * Description: Dynamic connectivity for forests, supports subtree aggregates. Nodes are 1-indexed.
 * Nodes are stored once and edges are stored twice, once in each direction. Subtrees are accessed by cutting the edge from subtree root to parent.
 * Source: self
 * Verification: https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum
 * Time: O(log n)
 */

const int MAX = 1e6 + 5;

struct Node {
    int sz, p, ch[2];
    bool node;
    long long val, sum, lazy;

    Node() : sz(0), p(0), ch(), node(false), val(0), sum(0), lazy(0) {}

    Node(int _val) : Node() {
        sz = node = 1;
        val = sum = _val;
    }
} tr[MAX];
int id = 1;

void push(int u) {
    if (!u)
        return;
    if (tr[u].lazy) {
        if (tr[u].node)
            tr[u].val += tr[u].lazy;
        tr[u].sum += tr[u].lazy * tr[u].sz;
        tr[tr[u].ch[0]].lazy += tr[u].lazy;
        tr[tr[u].ch[1]].lazy += tr[u].lazy;
        tr[u].lazy = 0;
    }
}

void pull(int u) {
    int l = tr[u].ch[0], r = tr[u].ch[1];
    push(l);
    push(r);
    tr[u].sz = tr[l].sz + tr[u].node + tr[r].sz;
    tr[u].sum = tr[l].sum + tr[u].val + tr[r].sum;
}

void attach(int u, int d, int v) {
    tr[u].ch[d] = v;
    tr[v].p = u;
    pull(u);
}

int dir(int u) {
    int v = tr[u].p;
    return tr[v].ch[0] == u ? 0 : tr[v].ch[1] == u ? 1 : -1;
}

void rotate(int u) {
    int v = tr[u].p, w = tr[v].p, du = dir(u), dv = dir(v);
    attach(v, du, tr[u].ch[!du]);
    attach(u, !du, v);
    if (~dv)
        attach(w, dv, u);
    else
        tr[u].p = w;
}

void splay(int u) {
    push(u);
    while (~dir(u)) {
        int v = tr[u].p, w = tr[v].p;
        push(w);
        push(v);
        push(u);
        int du = dir(u), dv = dir(v);
        if (~dv)
            rotate(du == dv ? v : u);
        rotate(u);
    }
}

int merge(int l, int r) {
    push(l);
    push(r);
    if (!l || !r)
        return l ? l : r;
    while (tr[l].ch[1]) {
        l = tr[l].ch[1];
        push(l);
    }
    splay(l);
    attach(l, 1, r);
    return l;
}

void detach(int u, int d) {
    int v = tr[u].ch[d];
    tr[u].ch[d] = tr[v].p = 0;
    pull(u);
}

void reroot(int u) {
    splay(u);
    int v = tr[u].ch[0];
    detach(u, 0);
    merge(u, v);
}

map<pair<int, int>, int> mp;

void link(int u, int v) {
    if (!mp.count({u, v})) {
        mp[{u, v}] = id++;
        mp[{v, u}] = id++;
    }
    int w = mp[{u, v}], x = mp[{v, u}];
    reroot(u);
    reroot(v);
    splay(u);
    splay(v);
    merge(merge(u, w), merge(v, x));
}

void cut(int u, int v) {
    int w = mp[{u, v}], x = mp[{v, u}];
    reroot(w);
    splay(w);
    detach(w, 1);
    splay(x);
    detach(x, 0);
    detach(x, 1);
}
