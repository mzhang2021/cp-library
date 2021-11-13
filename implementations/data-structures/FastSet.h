/**
 * Description: Faster alternative to std::multiset for adding, removing, and querying for max.
 * Source: self
 * Verification: https://codeforces.com/gym/103055/problem/B
 * Time: O(log n)
 */

template<typename T>
struct FastSet {
    priority_queue<T> pq, pending;

    void add(T x) {
        pq.push(x);
    }

    void rem(T x) {
        pending.push(x);
        while (!pq.empty() && !pending.empty() && pq.top() == pending.top()) {
            pq.pop();
            pending.pop();
        }
    }

    T max() {
        assert(!pq.empty());
        return pq.top();
    }
};
