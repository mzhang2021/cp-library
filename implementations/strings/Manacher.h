/**
 * Description: Finds the longest palindromic substring of a string. p[i] denotes the length of the longest palindrome centered at i, where if i is even, then centered on s[i / 2 - 1],
 * and if i is odd, then centered in between s[i / 2 - 1] and s[i / 2].
 * Source: https://www.youtube.com/watch?v=nbTSfrEfo6M
 * Verification: https://leetcode.com/problems/longest-palindromic-substring/
 * Time: O(n)
 */

#define MAXN 100000

int p[2*MAXN+3];

int manacher(const string &s) {
    memset(p, 0, sizeof(p));
    string t = "$";
    for (char c : s)
        t += '#', t += c;
    t += "#@";

    int c = 0, r = 0;
    for (int i=1; i<t.length()-1; i++) {
        int mirr = 2 * c - i;
        if (i < r)
            p[i] = min(p[mirr], r - i);
        while (t[i + (p[i] + 1)] == t[i - (p[i] + 1)])
            p[i]++;
        if (p[i] + i > r) {
            c = i;
            r = i + p[i];
        }
    }

    return *max_element(p, p + t.length());
}
