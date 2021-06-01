/**
 * Description: Segment tree variant built on intervals of values rather than indices.
 * Source: https://users.dcc.uchile.cl/~jperez/papers/ioiconf16.pdf
 * Verification: https://www.spoj.com/problems/ILKQUERY/
 * Time: O(n log n) build, O(log n) query and update
 */

struct WaveletTree {
    int s;
    vector<vector<int>> c;

    WaveletTree(vector<int> &a, int _s) : s(_s), c(2*s) {
        build(1, 0, s-1, a.begin(), a.end());
    }

    void build(int p, int l, int r, vector<int>::iterator b, vector<int>::iterator e) {
        if (l == r)
            return;

        int m = (l + r) / 2;
        c[p].push_back(0);
        for (auto it=b; it!=e; it++)
            c[p].push_back(c[p].back() + (*it <= m));

        auto mid = stable_partition(b, e, [&] (int i) {return i <= m;});
        build(2*p, l, m, b, mid);
        build(2*p+1, m+1, r, mid, e);
    }

    int query(int x, int i) {
        i++;
        int p = 1, l = 0, r = s - 1;
        while (l != r) {
            int m = (l + r) / 2, cnt = c[p][i];
            p *= 2;
            if (x <= m) {
                i = cnt;
                r = m;
            } else {
                i -= cnt;
                l = m + 1;
                p++;
            }
        }
        return i;
    }
};
