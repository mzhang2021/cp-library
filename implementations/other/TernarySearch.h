/**
 * Description: Searches for the extremum of a unimodal function in log n time.
 * Source: https://codeforces.com/blog/entry/11497
 * Verification: https://codeforces.com/problemset/problem/578/C
 * Time: O(log n)
 */

int f(int x);

int ternarySearch(int l, int r) {
    while (l < r) {
        int m = (l + r) / 2;
        if (f(m) > f(m+1))
            r = m;
        else
            l = m + 1;
    }
    return l;
}

double f(double x);

double ternarySearch(double l, double r) {
    for (int i=0; i<200; i++) {
        double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1) > f(m2))
            r = m2;
        else
            l = m1;
    }
    return l;
}
