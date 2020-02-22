/**
 * Description: Performs range prefix sum queries and point updates. Bounds are one-indexed on [1, x].
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time: O(log n) query and update
 */

#define MAXN 100000

int n, bit[MAXN+1];

int query(int x) {
    int ret = 0;
    for (int i=x; i>0; i-=i&-i)
        ret += bit[i];
    return ret;
}

void update(int x, int val) {
    for (int i=x; i<=n; i+=i&-i)
        bit[i] += val;
}
