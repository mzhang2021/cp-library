/**
 * Description: A randomized seed that's hack proof.
 * Source: https://codeforces.com/blog/entry/61587, https://codeforces.com/blog/entry/61675
 * Verification: seems fine
 * Time: O(1)
 */

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

// uniform_int_distribution<int>(a, b)(rng) generates a random integer between a and b inclusive
