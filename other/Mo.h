/**
 * Description: Offline algorithm for answering subarray queries.
 * Source: https://www.hackerearth.com/practice/notes/mos-algorithm/
 * Verification: https://codeforces.com/contest/220/problem/B
 * Time: O((n + q) sqrt(n))
 */

#define MAX 100000
#define SZ 300

struct Query {
    int l, r, idx;

    bool operator < (const Query &other) const {
        if (l / SZ == other.l / SZ)
            return (r < other.r) ^ (l / SZ % 2);
        return l / SZ < other.l / SZ;
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
        while (moLeft < queries[i].l)
            rem(moLeft++);
        while (moLeft > queries[i].l)
            add(--moLeft);
        while (moRight < queries[i].r)
            add(++moRight);
        while (moRight > queries[i].r)
            rem(moRight--);
        ret[queries[i].idx] = ans;
    }
}
