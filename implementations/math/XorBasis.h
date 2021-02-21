/**
 * Description: Finds an xor basis spanning the same vector space as an input of n d-dimensional vectors.
 * Source: https://codeforces.com/blog/entry/68953
 * Verification: https://www.spoj.com/problems/XMAX/
 * Time: O(n * d)
 */

const int LOG = 20;

int sz = 0, basis[LOG];

void add(int x) {
    for (int i=0; i<LOG; i++)
        if (x & (1 << i)) {
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                return;
            }
            x ^= basis[i];
        }
}
