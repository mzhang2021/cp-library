/**
 * Description: Decomposes graph into 2-edge-connected components and builds a bridge tree of them.
 * Source: self
 * Verification: https://codeforces.com/gym/100676 (problem H), https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-queries-on-the-graph/problem
 * Time: O(n + m)
 */

struct BridgeTree {
    int n, eid, ti;
    vector<int> num, id, stk;
    vector<vector<int>> tree, comp;
    vector<vector<pair<int, int>>> adj;

    BridgeTree(int _n) : n(_n), eid(0), ti(0), num(n), id(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, eid);
        adj[v].emplace_back(u, eid);
        eid++;
    }

    void init() {
        for (int u=0; u<n; u++)
            if (!num[u]) {
                dfs(u, -1);
                comp.emplace_back();
                while (!stk.empty()) {
                    id[stk.back()] = (int) comp.size() - 1;
                    comp.back().push_back(stk.back());
                    stk.pop_back();
                }
            }
        tree.resize(comp.size());
        for (auto &c : comp)
            for (int u : c)
                for (auto [v, i] : adj[u])
                    if (id[u] != id[v])
                        tree[id[u]].push_back(id[v]);
    }

    int dfs(int u, int p) {
        int low = num[u] = ++ti;
        stk.push_back(u);
        for (auto [v, i] : adj[u])
            if (i != p) {
                if (!num[v]) {
                    int ret = dfs(v, i);
                    low = min(low, ret);
                    if (num[u] < ret) {
                        comp.emplace_back();
                        do {
                            id[stk.back()] = (int) comp.size() - 1;
                            comp.back().push_back(stk.back());
                            stk.pop_back();
                        } while (comp.back().back() != v);
                    }
                } else {
                    low = min(low, num[v]);
                }
            }
        return low;
    }
};
