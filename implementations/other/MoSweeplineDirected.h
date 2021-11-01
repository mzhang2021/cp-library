/**
 * Description: Mo sweepline where the side of the range where we add an element matters.
 * Code below solves the problem "Sherlock and Inversions".
 * Source: https://codeforces.com/blog/entry/83248, https://discuss.codechef.com/t/dre3hgf-editorial/84967
 * Verification: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/sherlock-and-inversions/
 * Time: O((n + q) sqrt(n)) or O(n sqrt(q))
 */

const int SZ = 320;

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

void mo() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), sorted;
    for (int i=1; i<=n; i++) {
        cin >> a[i];
        sorted.push_back(a[i]);
    }
    vector<Query> queries(m);
    for (int i=0; i<m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int o = (int) sorted.size();
    for (int i=1; i<=n; i++)
        a[i] = int(lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin());

    vector<vector<tuple<int, int, int, int, int>>> iv(n + 1);
    sort(queries.begin(), queries.end());
    int moLeft = 1, moRight = 0;
    for (int i=0; i<m; i++) {
        Query &q = queries[i];
        if (moRight < q.r) {
            iv[moLeft - 1].emplace_back(moRight + 1, q.r, i, -1, 1);
            moRight = q.r;
        }
        if (q.l < moLeft) {
            iv[moRight].emplace_back(q.l, moLeft - 1, i, 1, 0);
            moLeft = q.l;
        }
        if (q.r < moRight) {
            iv[moLeft - 1].emplace_back(q.r + 1, moRight, i, 1, 1);
            moRight = q.r;
        }
        if (moLeft < q.l) {
            iv[moRight].emplace_back(moLeft, q.l - 1, i, -1, 0);
            moLeft = q.l;
        }
    }

    // adding from left -> query for values less than x -> prefix sum -> x contributes to a suffix
    // adding from right -> query for values greater than x -> suffix sum -> x contributes to a prefix
    vector<int> lcnt(o), llazy(SZ), rcnt(o), rlazy(SZ);

    auto add = [&] (int x) -> void {
        int b = x / SZ;
        for (int i=SZ-1; i>b; i--)
            llazy[i]++;
        for (int i=min((b+1)*SZ, o)-1; i>x; i--)
            lcnt[i]++;
        for (int i=0; i<b; i++)
            rlazy[i]++;
        for (int i=b*SZ; i<x; i++)
            rcnt[i]++;
    };

    auto query = [&] (int x, int s) -> int {
        return s ? rcnt[x] + rlazy[x / SZ] : lcnt[x] + llazy[x / SZ];
    };

    vector<long long> ans(m), ansPrev(n + 1), ansNext(n + 1);
    for (int i=1; i<=n; i++) {
        ansPrev[i] = ansPrev[i-1] + query(a[i], 1);
        add(a[i]);
        ansNext[i] = ansNext[i-1] + query(a[i], 0);
        for (auto [l, r, j, c, s] : iv[i]) {
            long long tot = 0;
            for (int p=l; p<=r; p++)
                tot += query(a[p], s);
            ans[j] += tot * c;
        }
    }

    vector<long long> ret(m);
    long long curAns = 0;
    for (int i=0; i<m; i++) {
        curAns += ans[i];
        ret[queries[i].idx] = curAns + ansPrev[queries[i].r] + ansNext[queries[i].l - 1];
    }

    for (int i=0; i<m; i++)
        cout << ret[i] << "\n";
}
