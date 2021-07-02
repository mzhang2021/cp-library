/**
 * Description: Performs range queries and point updates. Supports sparse indices.
 * Source: self
 * Verification: https://acm.timus.ru/problem.aspx?space=1&num=1439
 * Time: O(log n) query and update
 */

struct Node {
    int ans;
    Node *l, *r;

    Node() : ans(0), l(NULL), r(NULL) {}
};

int query(Node *p, int l, int r, int i, int j) {
    if (i > r || j < l || !p)
        return 0;
    if (i <= l && r <= j)
        return p->ans;
    int m = (l + r) / 2;
    return query(p->l, l, m, i, j) + query(p->r, m+1, r, i, j);
}

void update(Node *p, int l, int r, int idx, int val) {
    if (l == r) {
        p->ans = val;
        return;
    }
    int m = (l + r) / 2;
    if (idx <= m) {
        if (!p->l) p->l = new Node();
        update(p->l, l, m, idx, val);
    } else {
        if (!p->r) p->r = new Node();
        update(p->r, m+1, r, idx, val);
    }
    p->ans = (p->l ? p->l->ans : 0) + (p->r ? p->r->ans : 0);
}
