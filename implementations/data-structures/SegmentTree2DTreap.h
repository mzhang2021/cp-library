/**
 * Description: Performs 2D range queries and point updates using a treap for the inner dimension.
 * Source: self
 * Verification: https://oj.uz/problem/view/IOI13_game (but outer segtree needs to be dynamic)
 * Time: O(log^2 n) query and update
 */

#include "../other/RandomSeed.h"

struct SegmentTree2D {
    struct Node {
        int idx;
        long long val, ans;
        uint32_t priority;
        Node *l, *r;

        Node(int _idx, long long _val) : idx(_idx), val(_val), ans(_val), priority(rng()), l(NULL), r(NULL) {}
    };
    using pNode = Node*;

    long long ans(pNode t) {
        return t ? t->ans : 0;
    }

    void pull(pNode t) {
        if (t) t->ans = ans(t->l) + ans(t->r) + t->val;
    }

    void split(pNode t, pNode &l, pNode &r, int idx) {
        if (!t)
            l = r = NULL;
        else if (idx < t->idx)
            split(t->l, l, t->l, idx), r = t;
        else
            split(t->r, t->r, r, idx), l = t;
        pull(t);
    }

    void merge(pNode &t, pNode l, pNode r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->priority > r->priority)
            merge(l->r, l->r, r), t = l;
        else
            merge(r->l, l, r->l), t = r;
        pull(t);
    }

    long long query(pNode t, int l, int r) {
        pNode pl, pm, pr;
        split(t, pl, pm, l - 1);
        split(pm, t, pr, r);
        long long ret = ans(t);
        merge(pm, pl, t);
        merge(t, pm, pr);
        return ret;
    }

    void update(pNode &t, int p, long long val) {
        pNode pl, pm, pr;
        split(t, pl, pm, p - 1);
        split(pm, t, pr, p);
        if (t) t->val = t->ans = val;
        else t = new Node(p, val);
        merge(pm, pl, t);
        merge(t, pm, pr);
    }

    int n;
    vector<pNode> st;

    SegmentTree2D(int _n) : n(_n), st(2 * n) {}

    long long query(int ix, int iy, int jx, int jy) {
        long long ret = 0;
        for (ix+=n, jx+=n+1; ix<jx; ix>>=1, jx>>=1) {
            if (ix & 1) ret += query(st[ix++], iy, jy);
            if (jx & 1) ret += query(st[--jx], iy, jy);
        }
        return ret;
    }

    void update(int x, int y, long long val) {
        for (update(st[x+=n], y, val); x>1; x>>=1)
            update(st[x>>1], y, query(st[x], y, y) + query(st[x^1], y, y));
    }
};
