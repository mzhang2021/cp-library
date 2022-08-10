/**
 * Description: Randomized binary search tree that supports O(log n) split and merge functions.
 * Source: self
 * Verification: https://judge.yosupo.jp/submission/88983
 * Time: O(log n)
 */

#include "../other/RandomSeed.h"

const int MAX = 1e6 + 5;
const int MOD = 998244353;

struct Node {
    int sz, ch[2];
    uint32_t priority;
    long long val, sum, lazyB, lazyC;
    bool flip, lazy;

    Node() : sz(0), ch(), priority(rng()), val(0), sum(0), lazyB(1), lazyC(0), flip(false), lazy(false) {}

    Node(int _val) : Node() {
        sz = 1;
        val = sum = _val;
    }
} tr[MAX];
int id = 1;

void push(int p) {
    if (!p)
        return;
    if (tr[p].flip) {
        swap(tr[p].ch[0], tr[p].ch[1]);
        tr[tr[p].ch[0]].flip ^= true;
        tr[tr[p].ch[1]].flip ^= true;
        tr[p].flip = false;
    }
    if (tr[p].lazy) {
        tr[p].val = (tr[p].lazyB * tr[p].val + tr[p].lazyC) % MOD;
        tr[p].sum = (tr[p].lazyB * tr[p].sum + tr[p].lazyC * tr[p].sz) % MOD;
        for (int i=0; i<2; i++) {
            int u = tr[p].ch[i];
            if (u) {
                tr[u].lazyB = tr[u].lazyB * tr[p].lazyB % MOD;
                tr[u].lazyC = (tr[p].lazyB * tr[u].lazyC + tr[p].lazyC) % MOD;
                tr[u].lazy = true;
            }
        }
        tr[p].lazyB = 1;
        tr[p].lazyC = 0;
        tr[p].lazy = false;
    }
}

void pull(int p) {
    int l = tr[p].ch[0], r = tr[p].ch[1];
    push(l);
    push(r);
    tr[p].sz = tr[l].sz + tr[r].sz + 1;
    tr[p].sum = (tr[l].sum + tr[p].val + tr[r].sum) % MOD;
}

void heapify(int p) {
    if (!p)
        return;
    int mx = p;
    for (int i=0; i<2; i++) {
        int u = tr[p].ch[i];
        if (u && tr[u].priority > tr[mx].priority)
            mx = u;
    }
    if (mx != p) {
        swap(tr[p].priority, tr[mx].priority);
        heapify(mx);
    }
}

int build(const vector<int> &a, int l, int r) {
    if (l > r)
        return 0;
    int m = (l + r) / 2, p = id++;
    tr[p] = Node(a[m]);
    tr[p].ch[0] = build(a, l, m - 1);
    tr[p].ch[1] = build(a, m + 1, r);
    heapify(p);
    pull(p);
    return p;
}

pair<int, int> split(int p, int i, int add = 0) {
    if (!p)
        return {0, 0};
    push(p);
    int pos = tr[tr[p].ch[0]].sz + add;
    if (i < pos) {
        auto [l, r] = split(tr[p].ch[0], i, add);
        tr[p].ch[0] = r;
        pull(p);
        return {l, p};
    } else {
        auto [l, r] = split(tr[p].ch[1], i, pos + 1);
        tr[p].ch[1] = l;
        pull(p);
        return {p, r};
    }
}

int merge(int l, int r) {
    push(l);
    push(r);
    if (!l || !r)
        return l ? l : r;
    if (tr[l].priority > tr[r].priority) {
        tr[l].ch[1] = merge(tr[l].ch[1], r);
        pull(l);
        return l;
    } else {
        tr[r].ch[0] = merge(l, tr[r].ch[0]);
        pull(r);
        return r;
    }
}
