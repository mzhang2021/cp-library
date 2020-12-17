/**
 * Description: Used for DP problems where the KMP state is one of the parameters.
 * Source: https://codeforces.com/blog/entry/66943
 * Verification: https://codeforces.com/contest/1163/problem/D
 * Time: O(n)
 */

#define MAXM 1000

int m, lps[MAXM], nxt[MAXM+1][26];
string p;

void preprocess() {
    lps[0] = 0;
    int j = 0;
    for (int i=1; i<m; i++) {
        while (j != 0 && p[i] != p[j])
            j = lps[j-1];
        lps[i] = (j += (p[i] == p[j]));
    }

    for (int i=0; i<=m; i++)
        for (char c='a'; c<='z'; c++) {
            j = (i == m ? lps[m-1] : i);
            while (j != 0 && p[j] != c)
                j = lps[j-1];
            nxt[i][c-'a'] = (j += (p[j] == c));
        }
}
