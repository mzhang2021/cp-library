/**
 * Description: Offline algorithm for answering subarray queries. Supports updates to array.
 * Source: https://github.com/gkcs/Competitive-Programming/blob/master/src/main/java/main/java/videos/MosUpdate.java
 * Verification: https://www.spoj.com/problems/XXXXXXXX/
 * Time: O(n^(2/3) * q)
 */

#define MAX 10000
#define SZ 580

struct Query {
    int l, r, t, idx;

    bool operator < (const Query &other) const {
        if (l / SZ == other.l / SZ) {
            if (r / SZ == other.r / SZ)
                return t < other.t;
            return r / SZ < other.r / SZ;
        }
        return l / SZ < other.l / SZ;
    }
};

struct Update {
    int idx, val, last;
};

int q, a[MAX], ret[MAX];
Query queries[MAX];
Update updates[MAX];

int ans = 0;

void add(int i) {
    ans += a[i];
}

void rem(int i) {
    ans -= a[i];
}

void apply(int i) {
    updates[i].last = a[updates[i].idx];
    a[updates[i].idx] = updates[i].val;
}

void undo(int i) {
    a[updates[i].idx] = updates[i].last;
}

void mo() {
    sort(queries, queries + q);
    int moLeft = 0, moRight = -1, moTime = 0;
    for (int i=0; i<q; i++) {
        while (moTime < queries[i].t) {
            if (moLeft <= updates[moTime].idx && updates[moTime].idx <= moRight)
                rem(updates[moTime].idx);
            apply(moTime);
            if (moLeft <= updates[moTime].idx && updates[moTime].idx <= moRight)
                add(updates[moTime].idx);
            moTime++;
        }
        while (moTime > queries[i].t) {
            moTime--;
            if (moLeft <= updates[moTime].idx && updates[moTime].idx <= moRight)
                rem(updates[moTime].idx);
            undo(moTime);
            if (moLeft <= updates[moTime].idx && updates[moTime].idx <= moRight)
                add(updates[moTime].idx);
        }
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
