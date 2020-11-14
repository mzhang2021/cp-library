/**
 * Description: Basic combinatorial functions.
 * Source: own
 * Verification: https://www.spoj.com/problems/ADATEAMS/
 * Time: O(n log MOD) preprocessing
 */

const int MAX = 1e5 + 5;
const int MOD = 998244353;

long long fact[MAX], inv[MAX];

long long inverse(long long a) {
    long long ret = 1;
    for (int b=MOD-2; b>0; b/=2) {
        if (b % 2) ret = ret * a % MOD;
        a = a * a % MOD;
    }
    return ret;
}

long long choose(int n, int k) {
    if (k < 0 || n < k) return 0;
    return fact[n] * inv[k] % MOD * inv[n-k] % MOD;
}

void preprocess() {
    fact[0] = 1;
    for (int i=1; i<MAX; i++)
        fact[i] = fact[i-1] * i % MOD;
    inv[MAX-1] = inverse(fact[MAX-1]);
    for (int i=MAX-2; i>=0; i--)
        inv[i] = inv[i+1] * (i + 1) % MOD;
}
