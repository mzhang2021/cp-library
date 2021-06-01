/**
 * Description: Common operations for modular arithmetic. Mod inverse exists only when a is coprime with m.
 * Source: own
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Time: exponentiation and mod inverse are O(log n), other operations are O(1)
 */

#define MOD 998244353

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

void sub(int &a, int b) {
    a -= b;
    if (a < 0)
        a += MOD;
}

int mul(int a, int b) {
    return (long long) a * b % MOD;
}

int power(long long a, int b) {
    int ret = 1;
    while (b > 0) {
        if (b & 1)
            ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ret;
}

// uses Fermat's little theorem, works when modulus is prime
int inverse(long long a) {
    int ret = 1, b = MOD - 2;
    while (b > 0) {
        if (b & 1)
            ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ret;
}

// uses extended Euclidean algorithm
int inverseEuclidean(long long a) {
    long long m = MOD, x = 1, y = 0;
    while (a > 1) {
        long long q = a / m, t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += MOD;
    return x;
}
