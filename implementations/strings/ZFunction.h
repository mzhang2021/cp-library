/**
 * Description: Array computing longest common prefix between the string and each of its suffixes.
 * Source: https://cp-algorithms.com/string/z-function.html
 * Verification: https://codeforces.com/contest/126/problem/B
 * Time: O(n)
 */

#define MAXN 1000

int z[MAXN];

void preprocess(const string &s) {
    int n = s.length();
    for (int i=1, l=0, r=0; i<n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}
