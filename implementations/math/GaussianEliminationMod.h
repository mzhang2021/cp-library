/**
 * Description: Solves a system of linear equations of the form Ax = B, where A is [n x m], x is [m x 1], B is [n x 1].
 * Returns 0 if no solution, 1 if solution is unique, and 2 if there are infinitely many solutions.
 * Source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 * Verification: https://open.kattis.com/problems/equationsolver, https://open.kattis.com/problems/equationsolverplus
 * Time: O(min(n, m) * n * m)
 */

#include "ModInt.h"

using M = ModInt<998244353>;

int solve(vector<vector<M>> &a, vector<M> &b, vector<M> &x) {
    int n = (int) a.size(), m = (int) x.size();
    vector<int> pos(m, -1);
    for (int r=0, c=0; r<n && c<m; c++) {
        int pivot = r;
        for (int i=r+1; i<n; i++)
            if (a[i][c] != 0)
                pivot = i;
        if (a[pivot][c] == 0)
            continue;
        swap(a[r], a[pivot]);
        swap(b[r], b[pivot]);
        pos[c] = r;
        M inv = inverse(a[r][c]);
        for (int i=0; i<n; i++)
            if (i != r) {
                M f = a[i][c] * inv;
                for (int j=c; j<m; j++)
                    a[i][j] -= a[r][j] * f;
                b[i] -= b[r] * f;
            }
        r++;
    }
    x.assign(m, 0);
    bool inf = false;
    for (int j=0; j<m; j++) {
        if (pos[j] == -1)
            inf = true;
        else
            x[j] = b[pos[j]] / a[pos[j]][j];
    }
    for (int i=0; i<n; i++) {
        M sum = 0;
        for (int j=0; j<m; j++)
            sum += a[i][j] * x[j];
        if (sum != b[i])
            return 0;
    }
    return inf ? 2 : 1;
}
