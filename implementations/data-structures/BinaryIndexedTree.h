/**
 * Description: Performs range prefix sum queries and point updates. Bounds are one-indexed on [1, x].
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time: O(log n) query and update
 */

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int _n) : n(_n), bit(n + 1) {}

    T query(int i) {
        T ret = 0;
        for (; i>0; i-=i&-i)
            ret += bit[i];
        return ret;
    }

    T query(int l, int r) {
        return query(r) - query(l-1);
    }

    void update(int i, T val) {
        for (; i<=n; i+=i&-i)
            bit[i] += val;
    }
};
