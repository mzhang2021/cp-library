/**
 * Description: Performs range prefix sum queries and point updates. Bounds are one-indexed on [1, x].
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time: O(log n) query and update
 */

const int MAXN = 1e5 + 5;

int n, bit[MAXN];

int query(int i) {
    int ret = 0;
    for (; i>0; i-=i&-i)
        ret += bit[i];
    return ret;
}

void update(int i, int val) {
    for (; i<=n; i+=i&-i)
        bit[i] += val;
}
