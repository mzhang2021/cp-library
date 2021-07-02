/**
 * Description: Offline algorithm for answering subarray queries. Optimal block size is n / sqrt(q).
 * Source: https://www.hackerearth.com/practice/notes/mos-algorithm/
 * Verification: https://codeforces.com/contest/220/problem/B
 * Time: O((n + q) sqrt(n)) or O(n sqrt(q))
 */

const int SZ = 300;

struct Query {
    int l, r, idx;

    bool operator < (const Query &other) const {
        if (l / SZ == other.l / SZ) {
            if (r == other.r)
                return idx < other.idx;
            return l / SZ % 2 ? r > other.r : r < other.r;
        }
        return l < other.l;
    }
};

void mo(int q, const vector<int> &a, const vector<Query> &queries) {
    int ans = 0;

    auto add = [&] (int i) -> void {
        ans += a[i];
    };

    auto rem = [&] (int i) -> void {
        ans -= a[i];
    };

    sort(queries.begin(), queries.end());
    int moLeft = 0, moRight = -1;
    vector<int> ret(q);
    for (const Query &query : queries) {
        while (moLeft > query.l)
            add(--moLeft);
        while (moRight < query.r)
            add(++moRight);
        while (moLeft < query.l)
            rem(moLeft++);
        while (moRight > query.r)
            rem(moRight--);
        ret[query.idx] = ans;
    }
}
