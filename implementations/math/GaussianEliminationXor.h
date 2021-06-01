/**
 * Description: Gaussian elimination under mod 2 using bitset optimization.
 * Returns 0 if no solution, 1 if solution is unique, and 2 if there are infinitely many solutions.
 * Source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 * Verification: https://www.hackerearth.com/practice/algorithms/dynamic-programming/2-dimensional/practice-problems/algorithm/interesting-game-hard-93f267d9/
 * Time: O(min(n, m) * n * m)
 */

const int MAXM = 1005;

int solve(vector<bitset<MAXM>> &a, vector<int> &b, bitset<MAXM> &x, int m) {
    int n = (int) a.size();
    vector<int> pos(m, -1);
    for (int r=0, c=0; r<n && c<m; c++) {
        for (int i=r; i<n; i++)
            if (a[i][c]) {
                swap(a[i], a[r]);
                swap(b[i], b[r]);
                break;
            }
        if (!a[r][c])
            continue;
        pos[c] = r;
        for (int i=0; i<n; i++)
            if (i != r && a[i][c]) {
                a[i] ^= a[r];
                b[i] ^= b[r];
            }
        r++;
    }
    bool inf = false;
    for (int j=0; j<m; j++) {
        if (pos[j] == -1)
            inf = true;
        else
            x[j] = b[pos[j]];
    }
    for (int i=0; i<n; i++) {
        int sum = 0;
        for (int j=0; j<m; j++)
            sum ^= a[i][j] * x[j];
        if (sum != b[i])
            return 0;
    }
    return inf ? 2 : 1;
}
