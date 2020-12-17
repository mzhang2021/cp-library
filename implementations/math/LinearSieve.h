/**
 * Description: Computes all prime numbers less than n in linear time.
 * Source: https://codeforces.com/blog/entry/54090
 * Verification: https://open.kattis.com/problems/primesieve
 * Time: O(n)
 */

#define MAX 10000

bitset<MAX> prime;
vector<int> primeList;

void sieve() {
    prime.set();
    prime[0] = prime[1] = 0;
    for (int i=2; i<MAX; i++) {
        if (prime[i])
            primeList.push_back(i);
        for (int j : primeList) {
            if (i * j >= MAX)
                break;
            prime[i * j] = 0;
            if (i % j == 0)
                break;
        }
    }
}
