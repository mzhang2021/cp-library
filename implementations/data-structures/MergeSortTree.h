/**
 * Description: Stores vectors in nodes of segment tree. Change vector to ordered_set to support point updates.
 * Source: https://codeforces.com/blog/entry/15890
 * Verification: https://www.spoj.com/problems/KQUERYO/
 * Time: O(n log n) build, O(log^2 n) query
 */

#define MAXN 100000

int a[MAXN];
vector<int> st[4*MAXN];

void build(int p, int l, int r) {
    if (l == r) {
        st[p].push_back(a[l]);
        return;
    }

    int m = (l + r) / 2;
    build(2*p, l, m);
    build(2*p+1, m+1, r);
    merge(st[2*p].begin(), st[2*p].end(), st[2*p+1].begin(), st[2*p+1].end(), back_inserter(st[p]));
}

int query(int p, int l, int r, int i, int j, int k) {
    if (i > r || j < l)
        return 0;
    if (i <= l && r <= j)
        return st[p].end() - upper_bound(st[p].begin(), st[p].end(), k);

    int m = (l + r) / 2;
    return query(2*p, l, m, i, j, k) + query(2*p+1, m+1, r, i, j, k);
}
