/**
 * Description: Mo's algorithm modification that reduces number of updates to O(n) in exchange for increasing query count to O(n sqrt(n)).
 * Cnt array stores an element's contribution to the current prefix. Code below solves example problem in blog.
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1);
    for (int i=1; i<=n; i++)
        cin >> a[i];
    vector<int> s(k);
    for (int i=0; i<k; i++)
        cin >> s[i];
    vector<Query> queries(m);
    for (int i=0; i<m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    vector<vector<tuple<int, int, int, int>>> iv(n + 1);
    sort(queries.begin(), queries.end());
    int moLeft = 1, moRight = 0;
    for (int i=0; i<m; i++) {
        Query &q = queries[i];
        if (moRight < q.r) {
            iv[moLeft - 1].emplace_back(moRight + 1, q.r, i, -1);
            moRight = q.r;
        }
        if (q.l < moLeft) {
            iv[moRight].emplace_back(q.l, moLeft - 1, i, 1);
            moLeft = q.l;
        }
        if (q.r < moRight) {
            iv[moLeft - 1].emplace_back(q.r + 1, moRight, i, 1);
            moRight = q.r;
        }
        if (moLeft < q.l) {
            iv[moRight].emplace_back(moLeft, q.l - 1, i, -1);
            moLeft = q.l;
        }
    }

    vector<int> cnt(1 << 10);

    auto add = [&] (int x) -> void {
        for (int i=0; i<k; i++)
            cnt[x ^ s[i]]++;
    };

    vector<long long> ans(m), ansPrev(n + 1), ansNext(n + 1);
    for (int i=1; i<=n; i++) {
        ansPrev[i] = ansPrev[i-1] + cnt[a[i]];
        add(a[i]);
        ansNext[i] = ansNext[i-1] + cnt[a[i]];
        for (auto [l, r, j, c] : iv[i]) {
            long long tot = 0;
            for (int p=l; p<=r; p++)
                tot += cnt[a[p]];
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
