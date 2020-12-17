/**
 * Description: Persistent segment tree with lazy propagation.
 * Source: https://discuss.codechef.com/t/persistence-made-simple-tutorial/14915
 * Verification: https://www.spoj.com/problems/TTM/
 * Time: O(n) build, O(log n) query and update
 */

const int MAX = 2e7 + 5;

int id = 1, pl[MAX], pr[MAX], lazy[MAX];
long long st[MAX];

int newLeaf(int val) {
    int p = id++;
    pl[p] = pr[p] = 0;
    st[p] = val;
    return p;
}

int newParent(int a, int b) {
    int p = id++;
    pl[p] = a;
    pr[p] = b;
    st[p] = st[a] + st[b];
    return p;
}

int newLazy(int old, int val, int l, int r) {
    int p = id++;
    pl[p] = pl[old];
    pr[p] = pr[old];
    st[p] = st[old] + (long long) (r - l + 1) * val;
    lazy[p] = lazy[old] + val;
    return p;
}

void push(int p, int l, int r) {
    if (lazy[p]) {
        if (l != r) {
            int m = (l + r) / 2;
            pl[p] = newLazy(pl[p], lazy[p], l, m);
            pr[p] = newLazy(pr[p], lazy[p], m+1, r);
        }
        lazy[p] = 0;
    }
}

int build(int *a, int l, int r) {
    if (l == r)
        return newLeaf(a[l]);
    int m = (l + r) / 2;
    return newParent(build(a, l, m), build(a, m+1, r));
}

long long query(int p, int l, int r, int i, int j) {
    if (i > r || j < l)
        return 0;
    if (i <= l && r <= j)
        return st[p];
    push(p, l, r);
    int m = (l + r) / 2;
    return query(pl[p], l, m, i, j) + query(pr[p], m+1, r, i, j);
}

int update(int p, int l, int r, int i, int j, int val) {
    if (i > r || j < l)
        return p;
    if (i <= l && r <= j)
        return newLazy(p, val, l, r);
    push(p, l, r);
    int m = (l + r) / 2;
    return newParent(update(pl[p], l, m, i, j, val), update(pr[p], m+1, r, i, j, val));
}
