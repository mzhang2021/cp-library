/**
 * Description: Performs range minimum queries on a static array.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/RMQSQ/
 * Time: O(n log n) build, O(1) query
 */

template<int SZ, int LOG>
struct RMQ {
    int a[SZ], spt[SZ][LOG];

    RMQ(int n, int *_a) {
        for (int i=0; i<n; i++) {
            a[i] = _a[i];
            spt[i][0] = i;
        }

        for (int j=1; 1<<j<=n; j++)
            for (int i=0; i+(1<<j)<=n; i++) {
                if (a[spt[i][j-1]] < a[spt[i+(1<<(j-1))][j-1]])
                    spt[i][j] = spt[i][j-1];
                else
                    spt[i][j] = spt[i+(1<<(j-1))][j-1];
            }
    }

    int query(int i, int j) {
        int k = 31 - __builtin_clz(j - i + 1);
        return min(a[spt[i][k]], a[spt[j-(1<<k)+1][k]]);
    }
};
