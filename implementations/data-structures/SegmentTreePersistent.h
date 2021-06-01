/**
 * Description: Segment tree variant that supports querying on previous versions of the tree.
 * Source: https://discuss.codechef.com/t/persistence-made-simple-tutorial/14915
 * Verification: https://www.spoj.com/problems/MKTHNUM/
 * Time: O(n) build, O(log n) query and update
 */

const int MAX = 2e7 + 5;

int id = 1, pl[MAX], pr[MAX], st[MAX];

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

int build(int *a, int l, int r) {
    if (l == r)
        return newLeaf(a[l]);
    int m = (l + r) / 2;
    return newParent(build(a, l, m), build(a, m+1, r));
}

int query(int p, int l, int r, int i, int j) {
    if (i > r || j < l)
        return 0;
    if (i <= l && r <= j)
        return st[p];
    int m = (l + r) / 2;
    return query(pl[p], l, m, i, j) + query(pr[p], m+1, r, i, j);
}

int update(int p, int l, int r, int idx, int val) {
    if (l == r)
        return newLeaf(st[p] + val);
    int m = (l + r) / 2;
    if (idx <= m)
        return newParent(update(pl[p], l, m, idx, val), pr[p]);
    return newParent(pl[p], update(pr[p], m+1, r, idx, val));
}
