/**
 * Description: Recovers a nth-order linear recurrence relation from the first 2n terms. Solve can be sped up to O(n log n log k) with FFT as mul.
 * Source: https://codeforces.com/blog/entry/61306, https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/BerlekampMassey.h
 * Verification: https://codeforces.com/contest/506/problem/E
 * Time: O(n^2) BM, O(n^2 log k) solve
 */

template<typename T>
vector<T> berlekampMassey(const vector<T> &s) {
    int n = (int) s.size(), l = 0, m = 1;
    vector<T> b(n), c(n);
    T ld = b[0] = c[0] = 1;
    for (int i=0; i<n; i++, m++) {
        T d = s[i];
        for (int j=1; j<=l; j++)
            d += c[j] * s[i-j];
        if (d == 0)
            continue;
        vector<T> temp = c;
        T coef = d / ld;
        for (int j=m; j<n; j++)
            c[j] -= coef * b[j-m];
        if (2 * l <= i) {
            l = i + 1 - l;
            b = temp;
            ld = d;
            m = 0;
        }
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (T &x : c)
        x = -x;
    return c;
}

template<typename T>
T solve(const vector<T> &c, const vector<T> &s, long long k) {
    int n = (int) c.size();
    assert(c.size() <= s.size());

    auto mul = [&] (const vector<T> &a, const vector<T> &b) -> vector<T> {
        vector<T> ret(a.size() + b.size() - 1);
        for (int i=0; i<(int)a.size(); i++)
            for (int j=0; j<(int)b.size(); j++)
                ret[i+j] += a[i] * b[j];
        for (int i=(int)ret.size()-1; i>=n; i--)
            for (int j=n-1; j>=0; j--)
                ret[i-j-1] += ret[i] * c[j];
        ret.resize(min((int) ret.size(), n));
        return ret;
    };

    vector<T> a = n == 1 ? vector<T>{c[0]} : vector<T>{0, 1}, x{1};
    for (; k>0; k/=2) {
        if (k % 2)
            x = mul(x, a);
        a = mul(a, a);
    }
    x.resize(n);

    T ret = 0;
    for (int i=0; i<n; i++)
        ret += x[i] * s[i];
    return ret;
}
