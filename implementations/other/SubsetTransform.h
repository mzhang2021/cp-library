/**
 * Description: Various subset transforms and other tricks.
 * Source: https://codeforces.com/blog/entry/45223, https://codeforces.com/blog/entry/72488, https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
 * Verification: https://cses.fi/problemset/task/1654, https://codeforces.com/contest/914/problem/G
 */

// SOS DP, also known as Zeta transform, computes \sum_{S' \subseteq S} f(S') for all S in O(n * 2^n)
template<typename T>
vector<T> zetaTransform(int n, const vector<T> &f) {
    vector<T> dp = f;
    for (int i=0; i<n; i++)
        for (int mask=0; mask<1<<n; mask++)
            if (mask >> i & 1)
                dp[mask] += dp[mask ^ (1 << i)];    // change to dp[mask ^ (1 << i)] += dp[mask] for superset instead of subset sum
    return dp;
}

// Mobius transform (inclusion exclusion SOS), computes \sum_{S' \subseteq S} (-1)^{|S \setminus S'|} f(S') for all S in O(n * 2^n)
// also inverts the zeta transform (i.e. returns the input given an output)
template<typename T>
vector<T> mobiusTransform(int n, const vector<T> &f) {
    vector<T> dp = f;
    for (int i=0; i<n; i++)
        for (int mask=0; mask<1<<n; mask++)
            if (mask >> i & 1)
                dp[mask] -= dp[mask ^ (1 << i)];
    return dp;
}

// subset sum convolution, computes \sum_{S' \subseteq S} f(S') g(S \setminus S') for all S in O(n^2 * 2^n)
template<typename T>
vector<T> subsetConvolution(int n, const vector<T> &f, const vector<T> &g) {
    vector<vector<T>> fhat(n + 1, vector<T>(1 << n)), ghat(n + 1, vector<T>(1 << n)), h(n + 1, vector<T>(1 << n));
    for (int mask=0; mask<1<<n; mask++) {
        fhat[__builtin_popcount(mask)][mask] = f[mask];
        ghat[__builtin_popcount(mask)][mask] = g[mask];
    }
    for (int i=0; i<=n; i++) {
        fhat[i] = zetaTransform(n, fhat[i]);
        ghat[i] = zetaTransform(n, ghat[i]);
    }
    for (int mask=0; mask<1<<n; mask++)
        for (int i=0; i<=n; i++)
            for (int j=0; j<=i; j++)
                h[i][mask] += fhat[j][mask] * ghat[i-j][mask];
    for (int i=0; i<=n; i++)
        h[i] = mobiusTransform(n, h[i]);
    vector<T> ret(1 << n);
    for (int mask=0; mask<1<<n; mask++)
        ret[mask] = h[__builtin_popcount(mask)][mask];
    return ret;
}

// Gosper's hack, iterates over only subsets of size k
template<typename F>
void gosper(int n, int k, const F &f) {
    if (k == 0) {
        f(0);
        return;
    }
    int mask = (1 << k) - 1;
    while (mask < 1 << n) {
        f(mask);
        int a = mask & -mask, b = mask + a;
        mask = ((mask ^ b) >> 2) / a | b;
    }
}
