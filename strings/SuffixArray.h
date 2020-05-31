/**
 * Description: A data structure for solving a variety of string problems.
 * Source: https://cp-algorithms.com/string/suffix-array.html
 * Verification: https://www.spoj.com/problems/ADASTRNG/
 * Time: O(n log n) build
 */

struct SuffixArray {
    const int ALPHA = 256;
    int n;
    string s;
    vector<int> p, lcp;

    SuffixArray(string _s) : n(_s.length() + 1), s(_s), p(n), lcp(n-1) {
        s += '$';
        buildSA();
        buildLCP();
    }

    void buildSA() {
        vector<int> c(n), cnt(max(ALPHA, n));
        for (int i=0; i<n; i++)
            cnt[s[i]]++;
        for (int i=1; i<ALPHA; i++)
            cnt[i] += cnt[i-1];
        for (int i=0; i<n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i=1; i<n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        for (int j=0; 1<<j<n; j++) {
            for (int i=0; i<n; i++) {
                pn[i] = p[i] - (1 << j);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i=0; i<n; i++)
                cnt[c[pn[i]]]++;
            for (int i=1; i<classes; i++)
                cnt[i] += cnt[i-1];
            for (int i=n-1; i>=0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i=1; i<n; i++) {
                pair<int, int> cur(c[p[i]], c[(p[i] + (1 << j)) % n]), pre(c[p[i-1]], c[(p[i-1] + (1 << j)) % n]);
                if (cur != pre)
                    classes++;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
    }

    void buildLCP() {
        vector<int> rk(n);
        for (int i=0; i<n; i++)
            rk[p[i]] = i;

        int k = 0;
        for (int i=0; i<n; i++) {
            if (rk[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[rk[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k])
                k++;
            lcp[rk[i]] = k;
            if (k)
                k--;
        }
    }
};
