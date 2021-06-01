/**
 * Description: Maintains convex hull trick with segment tree, queries for minimum.
 * Source: https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
 * Verification: https://csacademy.com/contest/archive/task/squared-ends/statement/
 * Time: O(log C), C is maximum coordinate size
 */

const int MAX = 1e6 + 5;

struct Line {
    long long m, c;

    long long operator () (long long x) const {
        return m * x + c;
    }
};

Line st[4*MAX];

long long query(int p, int l, int r, long long x) {
    if (l + 1 == r)
        return st[p](x);
    int m = (l + r) / 2;
    if (x < m)
        return min(st[p](x), query(2*p, l, m, x));
    return min(st[p](x), query(2*p+1, m, r, x));
}

void update(int p, int l, int r, Line cur) {
    if (l + 1 == r || st[p].m == cur.m) {
        if (cur(l) < st[p](l))
            st[p] = cur;
        return;
    }
    int m = (l + r) / 2;
    if (st[p].m > cur.m)
        swap(st[p], cur);
    if (st[p](m) > cur(m)) {
        swap(st[p], cur);
        update(2*p+1, m, r, cur);
    } else {
        update(2*p, l, m, cur);
    }
}
