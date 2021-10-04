/**
 * Description: Primality test
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/MillerRabin.h
 * Verification: https://www.spoj.com/problems/PRIC/
 * Time: O(log n)
 */

using ull = unsigned long long;

ull mul(ull a, ull b, const ull MOD) {
    long long ret = a * b - MOD * ull(1.L / MOD * a * b);
    return ret + MOD * (ret < 0) - MOD * (ret >= (long long) MOD);
}

ull power(ull a, ull b, const ull MOD) {
    ull ret = 1;
    for (; b>0; b/=2) {
        if (b & 1) ret = mul(ret, a, MOD);
        a = mul(a, a, MOD);
    }
    return ret;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull a : A) {
        ull p = power(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = mul(p, p, n);
        if (p != n - 1 && i != s)
            return false;
    }
    return true;
}
