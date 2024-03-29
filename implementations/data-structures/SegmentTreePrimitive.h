/**
 * Description: Performs range queries and point updates.
 * Source: http://codeforces.com/blog/entry/18051
 * Verification: https://www.spoj.com/problems/FENTREE/
 * Time: O(n) build, O(log n) query and update
 */

template<typename T>
struct SegmentTree {
    int n;
    vector<T> st;

    SegmentTree(int _n) : n(_n), st(2 * n) {}

    SegmentTree(const vector<T> &a) : n((int) a.size()), st(2 * n) {
        for (int i=0; i<n; i++)
            st[i+n] = a[i];
        for (int i=n-1; i>0; i--)
            st[i] = st[i<<1] + st[i<<1|1];
    }

    T query(int l, int r) {
        T ret = 0;
        for (l+=n, r+=n+1; l<r; l>>=1, r>>=1) {
            if (l&1) ret += st[l++];
            if (r&1) ret += st[--r];
        }
        return ret;
    }

    void update(int p, T val) {
        for (st[p+=n]=val; p>1; p>>=1)
            st[p>>1] = st[p] + st[p^1];
    }
};
