/**
 * Description: A polynomial hash function for strings.
 * Source: https://codeforces.com/blog/entry/60445
 * Verification: https://acm.timus.ru/problem.aspx?space=1&num=1517
 */

const uint64_t MOD = (1ULL << 61) - 1;
const int BASE = [] () {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed ^ uint64_t(new uint64_t));
    uniform_int_distribution<int> dist(258, 2e9 - 1);
    int base = dist(gen);
    return base % 2 == 0 ? base - 1 : base;
} ();

uint64_t add(uint64_t a, uint64_t b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

uint64_t sub(uint64_t a, uint64_t b) {
    a -= b;
    if (a >= MOD)
        a += MOD;
    return a;
}

uint64_t mul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & MOD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & MOD) + (ret >> 61);
    ret = (ret & MOD) + (ret >> 61);
    return ret - 1;
}

uint64_t getHash(const string &s) {
    uint64_t ret = 0;
    for (char c : s)
        ret = add(mul(ret, BASE), c);
    return ret;
}

// A string with characters c_0 c_1 c_2 c_3 is encoded as c_0 * BASE^3 + c_1 * BASE^2 + c_2 * BASE + c_3
// If you precompute all prefixes, then you can get any substring from index i with length L
// pref[i + L - 1] - pref[i - 1] * BASE^L
