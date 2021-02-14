/**
 * Description: Offline algorithm for answering subarray queries. Optimal block size is n / sqrt(q).
 * Source: https://www.hackerearth.com/practice/notes/mos-algorithm/
 * Verification: https://codeforces.com/contest/220/problem/B
 * Time: O((n + q) sqrt(n)) or O(n sqrt(q))
 */

const int MAX = 1e5 + 5;
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

int q, a[MAX], ret[MAX];
Query queries[MAX];

int ans = 0;

void add(int i) {
    ans += a[i];
}

void rem(int i) {
    ans -= a[i];
}

void mo() {
    sort(queries, queries + q);
    int moLeft = 0, moRight = -1;
    for (int i=0; i<q; i++) {
        while (moLeft > queries[i].l)
            add(--moLeft);
        while (moRight < queries[i].r)
            add(++moRight);
        while (moLeft < queries[i].l)
            rem(moLeft++);
        while (moRight > queries[i].r)
            rem(moRight--);
        ret[queries[i].idx] = ans;
    }
}
