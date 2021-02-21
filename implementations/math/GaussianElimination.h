/**
 * Description: Solves a system of linear equations of the form Ax = B, where A is [n x m], x is [m x 1], B is [n x 1].
 * Returns 0 if no solution, 1 if solution is unique, and 2 if there are infinitely many solutions.
 * Source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 * Verification: https://open.kattis.com/problems/equationsolver, https://open.kattis.com/problems/equationsolverplus
 * Time: O(min(n, m) * n * m)
 */

const double EPS = 1e-9;

int solve(vector<vector<double>> &a, vector<double> &b, vector<double> &x) {
    int n = (int) a.size(), m = (int) x.size();
    vector<int> pos(m, -1);
    for (int r=0, c=0; r<n && c<m; c++) {
        int pivot = r;
        for (int i=r+1; i<n; i++)
            if (abs(a[i][c]) > abs(a[pivot][c]))
                pivot = i;
        if (abs(a[pivot][c]) < EPS)
            continue;
        for (int j=c; j<m; j++)
            swap(a[r][j], a[pivot][j]);
        swap(b[r], b[pivot]);
        pos[c] = r;
        for (int i=0; i<n; i++)
            if (i != r) {
                double f = a[i][c] / a[r][c];
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
        double sum = 0;
        for (int j=0; j<m; j++)
            sum += a[i][j] * x[j];
        if (abs(sum - b[i]) > EPS)
            return 0;
    }
    return inf ? 2 : 1;
}
