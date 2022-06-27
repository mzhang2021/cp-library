/**
 * Description: Maintains the sum of the k largest elements in a multiset.
 * Source: self
 * Verification: https://cses.fi/problemset/task/2426
 * Time: O(log n)
 */

template<typename T>
struct KLargest {
    int k;
    T sum;
    multiset<T> big, small;

    KLargest(int _k) : k(_k), sum(0) {}

    void add(T x) {
        if (k == 0)
            return;
        if ((int) big.size() < k || x > *big.begin()) {
            sum += x;
            big.insert(x);
            if ((int) big.size() > k) {
                sum -= *big.begin();
                small.insert(*big.begin());
                big.erase(big.begin());
            }
        } else {
            small.insert(x);
        }
    }

    void rem(T x) {
        if (k == 0)
            return;
        if ((int) big.size() < k || x >= *big.begin()) {
            sum -= x;
            big.erase(big.find(x));
            if ((int) big.size() < k && !small.empty()) {
                sum += *small.rbegin();
                big.insert(*small.rbegin());
                small.erase(prev(small.end()));
            }
        } else {
            small.erase(small.find(x));
        }
    }
};
