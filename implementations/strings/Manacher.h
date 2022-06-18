/**
 * Description: Finds the longest palindromic substring of a string. p[i] denotes the length of the longest palindrome centered at i,
 * where if i is even, then centered on s[i / 2 - 1], and if i is odd, then centered in between s[i / 2 - 1] and s[i / 2].
 * To recover the actual endpoints of each palindrome, use l = (i - p[i] - 1) / 2 and r = (i + p[i] - 3) / 2.
 * Source: https://www.youtube.com/watch?v=nbTSfrEfo6M
 * Verification: https://leetcode.com/problems/longest-palindromic-substring/
 * Time: O(n)
 */

vector<int> manacher(const string &s) {
    string t = "$";
    for (char c : s)
        t += '#', t += c;
    t += "#@";
    int n = (int) t.size(), c = 0, r = 0;
    vector<int> p(n - 1);
    for (int i=1; i<n-1; i++) {
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
    return p;
}
