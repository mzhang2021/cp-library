/**
 * Description: Treap variant that supports querying on previous versions of the tree.
 * If tight on memory, don't store priority explicitly and instead replace tr[l].priority > tr[r].priority in merge method
 * with rng() % (tr[l].sz + tr[r].sz) < tr[l].sz
 * Source: self
 * Verification: https://www.luogu.com.cn/problem/P5055, https://www.acmicpc.net/problem/19068
 * Time: O(log n)
 */

#include "../other/RandomSeed.h"

const int MAX = 2e7 + 5;

struct Node {
    int sz, ch[2];
    uint32_t priority;
    int val;
    long long sum;
    bool flip;

    Node() : sz(0), ch(), priority(rng()), val(0), sum(0), flip(false) {}

    Node(int _val) : Node() {
        sz = 1;
        val = sum = _val;
    }
} tr[MAX];
int id = 1;

int copy(int p) {
    if (!p)
        return 0;
    int q = id++;
    tr[q] = tr[p];
    return q;
}

void push(int p) {
    if (!p || !tr[p].flip)
        return;
    swap(tr[p].ch[0], tr[p].ch[1]);
    for (int i=0; i<2; i++) {
        tr[p].ch[i] = copy(tr[p].ch[i]);
        tr[tr[p].ch[i]].flip ^= true;
    }
    tr[p].flip = false;
}

void pull(int p) {
    int l = tr[p].ch[0], r = tr[p].ch[1];
    push(l);
    push(r);
    tr[p].sz = tr[l].sz + tr[r].sz + 1;
    tr[p].sum = tr[l].sum + tr[p].val + tr[r].sum;
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
    p = copy(p);
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
        l = copy(l);
        tr[l].ch[1] = merge(tr[l].ch[1], r);
        pull(l);
        return l;
    } else {
        r = copy(r);
        tr[r].ch[0] = merge(l, tr[r].ch[0]);
        pull(r);
        return r;
    }
}
