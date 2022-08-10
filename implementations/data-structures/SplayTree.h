/**
 * Description: Binary search tree that supports O(log n) split and merge functions.
 * Source: https://codeforces.com/blog/entry/75885
 * Verification: https://judge.yosupo.jp/submission/89100
 * Time: O(log n)
 */

const int MAX = 1e6 + 5;
const int MOD = 998244353;

struct Node {
    int sz, p, ch[2];
    long long val, sum, lazyB, lazyC;
    bool flip, lazy;

    Node() : sz(0), p(0), ch(), val(0), sum(0), lazyB(1), lazyC(0), flip(false), lazy(false) {}

    Node(int _val) : Node() {
        sz = 1;
        val = sum = _val;
    }
} tr[MAX];
int id = 1;

void push(int u) {
    if (!u)
        return;
    if (tr[u].flip) {
        swap(tr[u].ch[0], tr[u].ch[1]);
        tr[tr[u].ch[0]].flip ^= true;
        tr[tr[u].ch[1]].flip ^= true;
        tr[u].flip = false;
    }
    if (tr[u].lazy) {
        tr[u].val = (tr[u].lazyB * tr[u].val + tr[u].lazyC) % MOD;
        tr[u].sum = (tr[u].lazyB * tr[u].sum + tr[u].lazyC * tr[u].sz) % MOD;
        for (int i=0; i<2; i++) {
            int v = tr[u].ch[i];
            if (v) {
                tr[v].lazyB = tr[v].lazyB * tr[u].lazyB % MOD;
                tr[v].lazyC = (tr[u].lazyB * tr[v].lazyC + tr[u].lazyC) % MOD;
                tr[v].lazy = true;
            }
        }
        tr[u].lazyB = 1;
        tr[u].lazyC = 0;
        tr[u].lazy = false;
    }
}

void pull(int u) {
    int l = tr[u].ch[0], r = tr[u].ch[1];
    push(l);
    push(r);
    tr[u].sz = tr[l].sz + tr[r].sz + 1;
    tr[u].sum = (tr[l].sum + tr[u].val + tr[r].sum) % MOD;
}

void attach(int u, int d, int v) {
    tr[u].ch[d] = v;
    tr[v].p = u;
    pull(u);
}

int build(const vector<int> &a, int l, int r) {
    if (l > r)
        return 0;
    int m = (l + r) / 2, u = id++;
    tr[u] = Node(a[m]);
    attach(u, 0, build(a, l, m - 1));
    attach(u, 1, build(a, m + 1, r));
    return u;
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

int find(int u, int i, int add = 0) {
    assert(u);
    push(u);
    int pos = tr[tr[u].ch[0]].sz + add;
    if (pos == i) {
        splay(u);
        return u;
    } else if (pos > i) {
        return find(tr[u].ch[0], i, add);
    } else {
        return find(tr[u].ch[1], i, pos + 1);
    }
}

pair<int, int> split(int u, int i) {
    assert(i < tr[u].sz);
    if (i == -1)
        return {0, u};
    u = find(u, i);
    int v = tr[u].ch[1];
    tr[u].ch[1] = tr[v].p = 0;
    pull(u);
    return {u, v};
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
