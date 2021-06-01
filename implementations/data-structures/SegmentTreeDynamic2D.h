/**
 * Description: Performs 2D range queries and point updates. Supports sparse indices.
 * Source: self
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=601
 * Time: O(log^2 n) query and update
 */

#include "SegmentTreeDynamic.h"

struct Seg {
    Node *node;
    Seg *l, *r;

    Seg() : node(new Node()), l(NULL), r(NULL) {}
};

int n;

int query(Seg *p, int l, int r, int ix, int iy, int jx, int jy) {
    if (ix > r || jx < l || !p)
        return 0;
    if (ix <= l && r <= jx)
        return query(p->node, 0, n-1, iy, jy);
    int m = (l + r) / 2;
    return query(p->l, l, m, ix, iy, jx, jy) + query(p->r, m+1, r, ix, iy, jx, jy);
}

void update_y(Node *p, Node *pl, Node *pr, int l, int r, int y, int val) {
    if (l != r) {
        int m = (l + r) / 2;
        if (y <= m) {
            if (!p->l) p->l = new Node();
            update_y(p->l, pl ? pl->l : NULL, pr ? pr->l : NULL, l, m, y, val);
        } else {
            if (!p->r) p->r = new Node();
            update_y(p->r, pl ? pl->r : NULL, pr ? pr->r : NULL, m+1, r, y, val);
        }
    }
    p->ans = (pl ? pl->ans : 0) + (pr ? pr->ans : 0);
}

void update(Seg *p, int l, int r, int x, int y, int val) {
    if (l == r) {
        update(p->node, 0, n-1, y, val);
        return;
    }
    int m = (l + r) / 2;
    if (x <= m) {
        if (!p->l) p->l = new Seg();
        update(p->l, l, m, x, y, val);
    } else {
        if (!p->r) p->r = new Seg();
        update(p->r, m+1, r, x, y, val);
    }
    update_y(p->node, p->l ? p->l->node : NULL, p->r ? p->r->node : NULL, 0, n-1, y, val);
}
