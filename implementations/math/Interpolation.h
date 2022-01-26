/**
 * Description: Lagrange interpolation for points x = 0, 1, ..., n - 1.
 * Lagrange polynomial is \sum_{i=1}^n y_i \prod_{j=1, j \neq n}^n \frac{x - x_j}{x_i - x_j}.
 * For any arithmetic progression x = a, a + d, ..., a + (n - 1) * d, shift the polynomial and evaluate f(x) = g((x - a) / d).
 * For arbitrary n points, do naive O(n^2) computation of the formula above.
 * Source: https://codeforces.com/blog/entry/82953
 * Verification: https://codeforces.com/contest/622/problem/F
 * Time: O(n + log MOD)
 */

#include "Modular.h"

using M = ModInt<1000000007>;

M interpolate(const vector<M> &y, long long x) {
    int n = (int) y.size();
    if (x < n)
        return y[x];
    vector<M> pref(n + 1), suff(n + 1), inv(n + 1);
    M fact = pref[0] = suff[n] = 1;
    for (int i=0; i<n; i++) {
        pref[i+1] = pref[i] * (x - i);
        fact *= i + 1;
    }
    inv[n] = inverse(fact);
    for (int i=n-1; i>=0; i--) {
        suff[i] = suff[i+1] * (x - i);
        inv[i] = inv[i+1] * (i + 1);
    }
    M ret = 0;
    for (int i=0; i<n; i++)
        ret += (i % 2 == n % 2 ? -1 : 1) * y[i] * pref[i] * suff[i+1] * inv[i] * inv[n-i-1];
    return ret;
}
