/**
 * Description: Performs 2D range prefix sum queries and point updates. Bounds are one-indexed on [1, x][1, y].
 * Source: own
 * Verification: https://www.spoj.com/problems/MATSUM/
 * Time: O(log^2 n) query and update
 */

#define MAXN 100

int n, bit[MAXN+1][MAXN+1];

int query(int x, int y) {
    int ret = 0;
    for (int i=x; i>0; i-=i&-i)
        for (int j=y; j>0; j-=j&-j)
            ret += bit[i][j];
    return ret;
}

void update(int x, int y, int val) {
    for (int i=x; i<=n; i+=i&-i)
        for (int j=y; j<=n; j+=j&-j)
            bit[i][j] += val;
}
