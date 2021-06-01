/**
 * Description: Finds the minimum value in a sliding window.
 * Source: self
 * Verification: https://leetcode.com/problems/sliding-window-maximum/
 * Time: O(n)
 */

template<typename T>
struct MinDeque {
    int l = 0, r = 0;
    deque<pair<T, int>> dq;

    void push(T x) {
        while (!dq.empty() && x <= dq.back().first)
            dq.pop_back();
        dq.emplace_back(x, r++);
    }

    void pop() {
        assert(l < r);
        if (dq.front().second == l++)
            dq.pop_front();
    }

    T min() {
        assert(!dq.empty());
        return dq.front().first;
    }
};
