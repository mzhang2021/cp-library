/**
 * Description: Faster alternative to std::multiset for adding, removing, and querying for max.
 * Source: self
 * Verification: self
 * Time: O(log n)
 */

struct FastSet {
    priority_queue<int> pq;
    vector<int> pending;

    FastSet(int n) : pending(n) {}

    void add(int x) {
        pq.push(x);
    }

    void rem(int x) {
        pending[x]++;
        while (!pq.empty() && pending[pq.top()]) {
            pending[pq.top()]--;
            pq.pop();
        }
    }

    int max() {
        assert(!pq.empty());
        return pq.top();
    }
};
