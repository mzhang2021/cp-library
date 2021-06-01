/**
 * Description: Computes all prime numbers less than n.
 * Source: own
 * Verification: https://open.kattis.com/problems/primesieve
 * Time: O(n log log n)
 */

const int MAX = 10000;

bitset<MAX> prime;
vector<int> primeList;

void sieve() {
    prime.set();
    prime[0] = prime[1] = 0;
    primeList.push_back(2);
    for (int i=4; i<MAX; i+=2)
        prime[i] = 0;
    for (int p=3; p<MAX; p+=2)
        if (prime[p]) {
            primeList.push_back(p);
            for (int i=p; i<=(MAX-1)/p; i+=2)
                prime[i*p] = 0;
        }
}
