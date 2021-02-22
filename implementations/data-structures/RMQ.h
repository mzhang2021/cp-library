/**
 * Description: Performs range minimum queries on a static array.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/RMQSQ/
 * Time: O(n log n) build, O(1) query
 */

template<typename T>
struct RMQ {
    vector<vector<T>> spt;

    RMQ() {}

    RMQ(const vector<T> &a) : spt(1, a) {
        int n = (int) a.size();
        for (int j=1; 1<<j<=n; j++) {
            spt.emplace_back(n - (1 << j) + 1);
            for (int i=0; i+(1<<j)<=n; i++)
                spt[j][i] = min(spt[j-1][i], spt[j-1][i+(1<<(j-1))]);
        }
    }

    T query(int i, int j) {
        int k = __lg(j - i + 1);
        return min(spt[k][i], spt[k][j-(1<<k)+1]);
    }
};
