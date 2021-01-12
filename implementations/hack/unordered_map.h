/**
 * Description: Hack for unprotected unordered_map. Assumes input is array of N integers in range [1, MAX].
 * Submit generator to different compiler version depending on solution being hacked.
 * Learn about hack from https://ipsc.ksp.sk/2014/real/solutions/booklet.pdf
 * Source: self
 */

struct Hack {
    const int N = 1e6;
    const long long MAX = 1e9;

    void gen(int NUM_PRIMES = 1) {
        unordered_set<int> st;
        vector<int> cutoff;
        for (int i=0; i<N; i++) {
            st.insert(i);
            int bk = st.bucket_count();
            if (cutoff.empty() || bk != cutoff.back())
                cutoff.push_back(bk);
        }
        assert((int) cutoff.size() > NUM_PRIMES);

        pair<long long, int> best;
        for (int i=0; i<(int)cutoff.size()-1; i++)
            best = max(best, {min(MAX / cutoff[i+1], (long long) cutoff[i]) * (N - cutoff[i]), i + 1});
        int start = max(best.second, NUM_PRIMES);

        vector<long long> v;
        v.reserve(N);
        int cnt = 0;
        for (int i=start; i>=start-NUM_PRIMES+1; i--) {
            for (long long j=cutoff[i]; j<=MAX && cnt<cutoff[start-NUM_PRIMES]; j+=cutoff[i]) {
                bool ok = true;
                for (int k=start; k>i; k--)
                    if (j % cutoff[k] == 0) {
                        ok = false;
                        break;
                    }
                if (ok) {
                    v.push_back(j);
                    cnt++;
                }
            }
        }
        long long val = 1;
        while ((int) v.size() < cutoff[start-NUM_PRIMES]) {
            bool ok = true;
            for (int i=start-NUM_PRIMES+1; i<=start; i++)
                if (val % cutoff[i] == 0) {
                    ok = false;
                    break;
                }
            if (ok)
                v.push_back(val);
            val++;
        }
        for (int i=start-NUM_PRIMES+1; i<start; i++) {
            val = cutoff[i];
            for (int j=0; j<cutoff[i]-cutoff[i-1]; j++) {
                v.push_back(val);
                val += cutoff[i];
                if (val > MAX)
                    val = cutoff[i];
            }
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
