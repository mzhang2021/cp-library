/**
 * Description: Solves the 2-SAT problem. Use bitwise not operator for negation.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/DFS/TwoSAT%20(12.1).h
 * Verification: https://cses.fi/problemset/task/1684/
 * Time: O(n + m)
 */

#include "SCC.h"

struct TwoSat {
    int n;
    vector<int> ans;
    vector<pair<int, int>> edges;

    TwoSat(int _n = 0) : n(_n) {}

    int addVar() {
        return n++;
    }

    void addOr(int x, int y) {
        x = max(2 * x, -2 * x - 1), y = max(2 * y, -2 * y - 1);
        edges.emplace_back(x, y);
    }

    void addXor(int x, int y) {
        addOr(x, y);
        addOr(~x, ~y);
    }

    void addNand(int x, int y) {
        addOr(~x, ~y);
    }

    void equals(int x, int y) {
        addOr(~x, y);
        addOr(x, ~y);
    }

    void implies(int x, int y) {
        addOr(~x, y);
    }

    void set(int x) {
        addOr(x, x);
    }

    void atMostOne(const vector<int> &v) {
        if (v.size() <= 1)
            return;
        int cur = ~v[0];
        for (int i=1; i<(int)v.size()-1; i++) {
            int nxt = addVar();
            addOr(cur, ~v[i]);
            addOr(cur, nxt);
            addOr(~v[i], nxt);
            cur = ~nxt;
        }
        addOr(cur, ~v.back());
    }

    bool solve() {
        SCC scc(2 * n);
        for (auto &e : edges) {
            scc.addEdge(e.first ^ 1, e.second);
            scc.addEdge(e.second ^ 1, e.first);
        }
        scc.init();
        for (int u=0; u<2*n; u+=2)
            if (scc.id[u] == scc.id[u+1])
                return false;
        ans.assign(n, -1);
        for (auto &c : scc.comp)
            for (int u : c)
                if (ans[u/2] == -1)
                    ans[u/2] = u % 2 == 0;
        return true;
    }
};
