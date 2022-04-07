/**
 * Description: Builds tree of "good ranges", or subarrays of a permutation that contain contiguous values.
 * type[i] = 0 if it's a cut node and 1 or 2 if it's a join node in ascending or descending order respectively.
 * For join nodes, any contiguous subsequence of children form a good range.
 * For cut nodes, no contiguous subsequence of children except for all or just one child is good.
 * Source: https://codeforces.com/blog/entry/78898
 * Verification: https://codeforces.com/contest/526/problem/F, https://codeforces.com/gym/101620/problem/I
 * Time: O(n log n) build time
 */

struct PermutationTree {
    struct SegmentTree {
        int n;
        vector<int> ans, lazy;

        SegmentTree(int _n) : n(_n), ans(4 * n), lazy(4 * n) {}

        void push(int p, bool leaf) {
            if (lazy[p]) {
                ans[p] += lazy[p];
                if (!leaf) {
                    lazy[2*p] += lazy[p];
                    lazy[2*p+1] += lazy[p];
                }
                lazy[p] = 0;
            }
        }

        int query(int p, int l, int r, int i, int j) {
            push(p, l == r);
            if (i > r || j < l)
                return INT_MAX;
            if (i <= l && r <= j)
                return ans[p];
            int m = (l + r) / 2;
            return min(query(2 * p, l, m, i, j), query(2 * p + 1, m + 1, r, i, j));
        }

        void update(int p, int l, int r, int i, int j, int v) {
            push(p, l == r);
            if (i > r || j < l)
                return;
            if (i <= l && r <= j) {
                lazy[p] += v;
                push(p, l == r);
                return;
            }
            int m = (l + r) / 2;
            update(2 * p, l, m, i, j, v);
            update(2 * p + 1, m + 1, r, i, j, v);
            ans[p] = min(ans[2*p], ans[2*p+1]);
        }

        int query(int l, int r) {
            return query(1, 0, n - 1, l, r);
        }

        void update(int l, int r, int v) {
            update(1, 0, n - 1, l, r, v);
        }
    };

    vector<int> a, stk, mnStk, mxStk, type;
    vector<pair<int, int>> range, span;
    vector<vector<int>> adj;
    SegmentTree st;

    PermutationTree(int n) : mnStk({-1}), mxStk({-1}), type(n), range(n), span(n), adj(n), st(n) {
        a.reserve(n);
    }

    PermutationTree(const vector<int> &p) : PermutationTree((int) p.size()) {
        for (int x : p)
            extend(x);
    }

    bool adjacent(int i, int j) {
        return range[i].second + 1 == range[j].first;
    }

    pair<int, int> getRange(const pair<int, int> &p, const pair<int, int> &q) {
        return {min(p.first, q.first), max(p.second, q.second)};
    }

    void extend(int x) {
        int i = (int) a.size();
        a.push_back(x);
        while (mnStk.back() != -1 && x < a[mnStk.back()]) {
            int j = mnStk.back();
            mnStk.pop_back();
            st.update(mnStk.back() + 1, j, a[j] - x);
        }
        mnStk.push_back(i);
        while (mxStk.back() != -1 && x > a[mxStk.back()]) {
            int j = mxStk.back();
            mxStk.pop_back();
            st.update(mxStk.back() + 1, j, x - a[j]);
        }
        mxStk.push_back(i);
        range[i] = {x, x};
        span[i] = {i, i};
        int u = i;
        while (!stk.empty()) {
            if (adjacent(stk.back(), u) || adjacent(u, stk.back())) {
                if ((adjacent(stk.back(), u) && type[stk.back()] == 1) || (adjacent(u, stk.back()) && type[stk.back()] == 2)) {
                    range[stk.back()] = getRange(range[stk.back()], range[u]);
                    span[stk.back()] = getRange(span[stk.back()], span[u]);
                    adj[stk.back()].push_back(u);
                    u = stk.back();
                } else {
                    type.push_back(adjacent(stk.back(), u) ? 1 : 2);
                    range.push_back(getRange(range[stk.back()], range[u]));
                    span.push_back(getRange(span[stk.back()], span[u]));
                    adj.push_back({stk.back(), u});
                    u = (int) type.size() - 1;
                }
                stk.pop_back();
            } else if (span[u].first > 0 && st.query(0, span[u].first - 1) == 0) {
                type.push_back(0);
                range.push_back(range[u]);
                span.push_back(span[u]);
                adj.push_back({u});
                u = (int) type.size() - 1;
                do {
                    range[u] = getRange(range[u], range[stk.back()]);
                    span[u] = getRange(span[u], span[stk.back()]);
                    adj[u].push_back(stk.back());
                    stk.pop_back();
                } while (range[u].second - range[u].first != span[u].second - span[u].first);
                reverse(adj[u].begin(), adj[u].end());
            } else {
                break;
            }
        }
        stk.push_back(u);
        st.update(0, i, -1);
    }
};
