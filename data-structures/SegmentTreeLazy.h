/**
 * Description: Performs range queries and range updates via lazy propagation. Bounds are zero-indexed on [l, r].
 * Source: https://www.hackerearth.com/practice/notes/segment-tree-and-lazy-propagation/
 * Verification: https://www.spoj.com/problems/HORRIBLE/
 * Time: O(n) build, O(log n) query and update
 */

template<int SZ>
struct SegmentTree {
    int st[4*SZ], lazy[4*SZ];

    SegmentTree() {
        memset(st, 0, sizeof(st));
        memset(lazy, 0, sizeof(lazy));
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
};
