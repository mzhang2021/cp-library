/**
 * Description: Every distinct substring corresponds to an execution in the automaton.
 * All substrings ending at the same state end at the same set of positions in the string (same equiv class).
 * The suffix link of state of substring w leads to the state of longest suffix of w with larger equiv class.
 * The suffix links form a tree, and we can compute equiv class sizes bottom-up on this tree.
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Verification: https://cses.fi/problemset/task/2108, https://www.spoj.com/problems/SUBLEX/
 * Time: O(n) build
 */

template<int ALPHA>
struct SuffixAutomaton {
    int last;
    vector<int> len, link;
    vector<array<int, ALPHA>> nxt;

    SuffixAutomaton() : last(0), len(1), link(1, -1), nxt(1) {}

    SuffixAutomaton(const string &s) : SuffixAutomaton() {
        for (char c : s)
            extend(c);
    }

    int getIndex(char c) {
        return c - 'a';
    }

    void extend(char c) {
        int cur = (int) len.size(), i = getIndex(c), p = last;
        len.push_back(len[last] + 1);
        link.emplace_back();
        nxt.emplace_back();
        while (p != -1 && !nxt[p][i]) {
            nxt[p][i] = cur;
            p = link[p];
        }
        if (p != -1) {
            int q = nxt[p][i];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                int clone = (int) len.size();
                len.push_back(len[p] + 1);
                link.push_back(link[q]);
                nxt.push_back(nxt[q]);
                while (p != -1 && nxt[p][i] == q) {
                    nxt[p][i] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
};
