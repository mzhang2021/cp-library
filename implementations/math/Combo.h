/**
 * Description: Basic combinatorial functions.
 * Source: own
 * Verification: https://www.spoj.com/problems/ADATEAMS/
 * Time: O(n) preprocessing
 */

#include "Modular.h"

typedef ModInt<998244353> M;

const int MAX = 1e5 + 5;

M fact[MAX], inv[MAX];

M choose(int n, int k) {
    if (k < 0 || n < k) return 0;
    return fact[n] * inv[k] * inv[n-k];
}

void preprocess() {
    fact[0] = 1;
    for (int i=1; i<MAX; i++)
        fact[i] = fact[i-1] * i;
    inv[MAX-1] = inverse(fact[MAX-1]);
    for (int i=MAX-2; i>=0; i--)
        inv[i] = inv[i+1] * (i + 1);
}
