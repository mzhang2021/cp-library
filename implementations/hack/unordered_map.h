/**
 * Description: Hack for unprotected unordered_map. Assumes input is array of N integers in range [1, MAX].
 * Submit generator to different compiler version depending on solution being hacked.
 * Learn about hack from https://ipsc.ksp.sk/2014/real/solutions/booklet.pdf
 * Source: self
 */

struct Hack {
    const int N = 1e6;
    const long long MAX = 1e9;

    void gen() {
        unordered_set<int> st;
        vector<int> cutoff;
        for (int i=0; i<N; i++) {
            st.insert(i);
            int bk = st.bucket_count();
            if (cutoff.empty() || bk != cutoff.back())
                cutoff.push_back(bk);
        }

        pair<long long, int> best;
        for (int i=0; i<(int)cutoff.size()-1; i++)
            best = max(best, {min(MAX / cutoff[i+1], (long long) cutoff[i]) * (N - cutoff[i]), i + 1});
        int start = best.second;

        vector<long long> v;
        v.reserve(N);
        for (long long x=cutoff[start]; x<=MAX; x+=cutoff[start])
            v.push_back(x);
        long long val = 1;
        while ((int) v.size() < cutoff[start]) {
            if (val % cutoff[start] != 0)
                v.push_back(val);
            val++;
        }
        val = cutoff[start];
        while ((int) v.size() < N) {
            v.push_back(val);
            val += cutoff[start];
            if (val > MAX)
                val = cutoff[start];
        }

        cout << N << "\n";
        for (int i=0; i<N; i++)
            cout << v[i] << " \n"[i==N-1];
    }
};
