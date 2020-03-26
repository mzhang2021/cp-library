/**
 * Description: Finds a x that satisfies k congruences. x mod lcm is unique.
 * Source: https://codeforces.com/blog/entry/61290
 * Verification: https://open.kattis.com/problems/generalchineseremainder
 * Time: O(k log n)
 */

#define MAX 100000

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return d;
}

bool solve(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    g = gcd(a, b, x0, y0);
    if (c % g)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    return true;
}

inline long long normalize(long long x, long long mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

int k;
long long a[MAX], m[MAX];

pair<long long, long long> crt() {
    long long ret = a[0], lcm = m[0];
    for (int i=1; i<k; i++) {
        long long x, y, d;
        if (!solve(lcm, m[i], a[i] - ret, x, y, d))
            return {-1, -1};    // no solution

        ret = normalize(ret + x % (m[i] / d) * lcm, lcm * m[i] / d);
        lcm = lcm * m[i] / d;
    }
    return {ret, lcm};
}
