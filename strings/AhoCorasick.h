/**
 * Description: A finite state automaton containing a dictionary of words, can efficiently find occurrence of words in a given string.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
 * Time: O(sum of lengths) build time
 */

#define MAX 100000
#define ALPHA 26

int id = 1, trie[MAX][ALPHA], link[MAX];

void add(const string &s) {
    int u = 0;
    for (char c : s) {
        if (!trie[u][c-'a'])
            u = trie[u][c-'a'] = id++;
        else
            u = trie[u][c-'a'];
    }
}

void gen() {
    link[0] = -1;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int j=0; j<ALPHA; j++) {
            int v = trie[u][j];
            if (v) {
                link[v] = (link[u] == -1 ? 0 : trie[link[u]][j]);
                q.push(v);
            } else if (u) {
                trie[u][j] = trie[link[u]][j];
            }
        }
    }
}
