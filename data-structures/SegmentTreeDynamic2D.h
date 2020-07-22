/**
 * Description: Performs 2D range queries and point updates. Supports sparse indices.
 * Source: self
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=601
 * Time: O(log^2 n) query and update
 */

#include "SegmentTreeDynamic.h"

struct Seg {
    int n, l, r;
    Node yNode;
    Seg *left, *right;

    Seg(int _n, int _l, int _r) : n(_n), l(_l), r(_r), yNode(0, n-1), left(NULL), right(NULL) {}

    void extend() {
        if (!left) {
            int m = (l + r) / 2;
            left = new Seg(n, l, m);
            right = new Seg(n, m+1, r);
        }
    }

    int query(int ix, int iy, int jx, int jy) {
        if (ix > r || jx < l)
            return 0;
        if (ix <= l && r <= jx)
            return yNode.query(iy, jy);

        extend();
        return left->query(ix, iy, jx, jy) + right->query(ix, iy, jx, jy);
    }

    void update(int x, int y, int val) {
        if (l == r) {
            yNode.update(y, val);
            return;
        }

        extend();
        int m = (l + r) / 2;
        if (x <= m)
            left->update(x, y, val);
        else
            right->update(x, y, val);
        update_y(&yNode, &left->yNode, &right->yNode, y, val);
    }

    void update_y(Node *cur, Node *curL, Node *curR, int y, long long val) {
        if (cur->l == cur->r) {
            cur->ans = curL->ans + curR->ans;
            return;
        }

        cur->extend();
        curL->extend();
        curR->extend();
        int m = (cur->l + cur->r) / 2;
        if (y <= m)
            update_y(cur->left, curL->left, curR->left, y, val);
        else
            update_y(cur->right, curL->right, curR->right, y, val);
        cur->ans = cur->left->ans + cur->right->ans;
    }
};
