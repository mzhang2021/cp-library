/**
 * Description: Performs range queries and range updates via lazy propagation. Bounds are zero-indexed on [l, r].
 * Source: https://www.hackerearth.com/practice/notes/segment-tree-and-lazy-propagation/
 * Verification: https://www.spoj.com/problems/HORRIBLE/
 * Time: O(n) build, O(log n) query and update
 */

struct SegmentTree {
    int n;
    vector<int> a, st, lazy;

    SegmentTree(int _n) : n(_n), st(4*n), lazy(4*n) {}

    SegmentTree(const vector<int> &_a) : n((int) _a.size()), a(_a), st(4*n), lazy(4*n) {
        build(1, 0, n-1);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            st[p] += a[l];
            return;
        }

        int m = (l + r) / 2;
        build(2*p, l, m);
        build(2*p+1, m+1, r);
        st[p] = st[2*p] + st[2*p+1];
    }

    void push(int p, int l, int r) {
        if (lazy[p]) {
            st[p] += (r - l + 1) * lazy[p];
            if (l != r) {
                lazy[2*p] += lazy[p];
                lazy[2*p+1] += lazy[p];
            }
            lazy[p] = 0;
        }
    }

    int query(int p, int l, int r, int i, int j) {
        push(p, l, r);

        if (i > r || j < l)
            return 0;
        if (i <= l && r <= j)
            return st[p];

        int m = (l + r) / 2;
        return query(2*p, l, m, i, j) + query(2*p+1, m+1, r, i, j);
    }

    int query(int i, int j) {
        return query(1, 0, n-1, i, j);
    }

    void update(int p, int l, int r, int i, int j, int val) {
        push(p, l, r);

        if (i > r || j < l)
            return;
        if (i <= l && r <= j) {
            st[p] += (r - l + 1) * val;
            if (l != r) {
                lazy[2*p] += val;
                lazy[2*p+1] += val;
            }
            return;
        }

        int m = (l + r) / 2;
        update(2*p, l, m, i, j, val);
        update(2*p+1, m+1, r, i, j, val);
        st[p] = st[2*p] + st[2*p+1];
    }

    void update(int i, int j, int val) {
        update(1, 0, n-1, i, j, val);
    }
};
