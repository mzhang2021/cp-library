/**
 * Description: Finds all occurrences of a pattern string in a text string.
 * Prefix function computes longest proper prefix that matches suffix for each prefix.
 * Source: https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
 * Verification: https://codeforces.com/contest/126/problem/B
 * Time: O(n + m)
 */

#define MAXM 1000

string t, p;
int n, m, lps[MAXM];

void preprocess() {
    lps[0] = 0;
    int j = 0;
    for (int i=1; i<m; i++) {
        while (j != 0 && p[i] != p[j])
            j = lps[j-1];
        lps[i] = (j += (p[i] == p[j]));
    }
}

vector<int> kmp() {
    preprocess();
    vector<int> ret;
    int j = 0;
    for (int i=0; i<n; i++) {
        while (j != 0 && t[i] != p[j])
            j = lps[j-1];
        if ((j += (t[i] == p[j])) == m) {
            ret.push_back(i - j + 1);
            j = lps[j-1];
        }
    }
    return ret;
}
