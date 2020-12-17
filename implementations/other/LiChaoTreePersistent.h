/**
 * Description: Persistent Li Chao tree.
 * Source: self
 * Verification: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=725&page=show_problem&problem=5642
 * Time: O(log C), C is maximum coordinate size
 */

const int MAX = 3e6 + 5;

struct Line {
    long long m, c;

    long long operator () (long long x) const {
        return m * x + c;
    }
};

int id, pl[MAX], pr[MAX];
Line st[MAX];

int newLeaf(const Line &cur) {
    int p = id++;
    pl[p] = pr[p] = 0;
    st[p] = cur;
    return p;
}

int newParent(int a, int b, const Line &cur) {
    int p = id++;
    pl[p] = a;
    pr[p] = b;
    st[p] = cur;
    return p;
}

long long query(int p, int l, int r, long long x) {
    if (l + 1 == r)
        return st[p](x);
    int m = (l + r) / 2;
    if (x < m)
        return min(st[p](x), pl[p] ? query(pl[p], l, m, x) : LLONG_MAX);
    return min(st[p](x), pr[p] ? query(pr[p], m, r, x) : LLONG_MAX);
}

int update(int p, int l, int r, const Line &cur) {
    if (p == 0)
        return newLeaf(cur);
    if (l + 1 == r)
        return cur(l) < st[p](l) ? newLeaf(cur) : p;
    int m = (l + r) / 2;
    if (st[p].m < cur.m) {
        if (st[p](m) > cur(m))
            return newParent(pl[p], update(pr[p], m, r, st[p]), cur);
        return newParent(update(pl[p], l, m, cur), pr[p], st[p]);
    } else if (st[p].m > cur.m) {
        if (st[p](m) > cur(m))
            return newParent(update(pl[p], l, m, st[p]), pr[p], cur);
        return newParent(pl[p], update(pr[p], m, r, cur), st[p]);
    } else {
        return st[p].c > cur.c ? newParent(pl[p], pr[p], cur) : p;
    }
}
