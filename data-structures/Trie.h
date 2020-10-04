/**
 * Description: A tree data structure for efficient string and binary number queries.
 * Source: https://codeforces.com/blog/entry/55782
 * Verification: https://www.spoj.com/problems/SUBXOR/
 * Time: O(length) insertion and query
 */

#define MAX 100000
#define ALPHA 26

int id = 1, trie[MAX][ALPHA], cnt[MAX];

void add(const string &s) {
    int u = 0;
    cnt[u]++;
    for (char c : s) {
        if (!trie[u][c-'a'])
            trie[u][c-'a'] = id++;
        u = trie[u][c-'a'];
        cnt[u]++;
    }
}

int query(const string &s) {
    int u = 0;
    for (char c : s) {
        if (!trie[u][c-'a'])
            return 0;
        u = trie[u][c-'a'];
    }
    return cnt[u];
}
