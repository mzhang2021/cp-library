/**
 * Description: Multiplies two polynomials quickly.
 * Source: https://cp-algorithms.com/algebra/fft.html
 * Verification: https://www.spoj.com/problems/POLYMUL/
 * Time: O(n log n)
 */

using cd = complex<double>;

const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    for (int i=1, j=0; i<n; i++) {
        int bit = n >> 1;
        for (; j&bit; bit>>=1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len=2; len<=n; len*=2) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            cd w(1);
            for (int j=0; j<len/2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv)
        for (cd &x : a)
            x /= n;
}

vector<long long> mul(const vector<long long> &a, const vector<long long> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) a.size() + (int) b.size())
        n *= 2;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i=0; i<n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> ret(n);
    for (int i=0; i<n; i++)
        ret[i] = llround(fa[i].real());
    return ret;
}
