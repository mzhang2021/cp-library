/**
 * Description: Performs range minimum queries on a static array.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/RMQSQ/
 * Time: O(n log n) build, O(1) query
 */

struct RMQ {
    vector<int> a;
    vector<vector<int>> spt;

    void init(int n, int *_a) {
        a.resize(n);
        spt.assign(1, vector<int>(n));
        for (int i=0; i<n; i++) {
            a[i] = _a[i];
            spt[0][i] = i;
        }

        for (int j=1; 1<<j<=n; j++) {
            spt.emplace_back(n - (1 << j) + 1);
            for (int i=0; i+(1<<j)<=n; i++) {
                if (a[spt[j-1][i]] < a[spt[j-1][i+(1<<(j-1))]])
                    spt[j][i] = spt[j-1][i];
                else
                    spt[j][i] = spt[j-1][i+(1<<(j-1))];
            }
        }
    }

    int query(int i, int j) {
        int k = 31 - __builtin_clz(j - i + 1);
        if (a[spt[k][i]] < a[spt[k][j-(1<<k)+1]])
            return spt[k][i];
        else
            return spt[k][j-(1<<k)+1];
    }
};
