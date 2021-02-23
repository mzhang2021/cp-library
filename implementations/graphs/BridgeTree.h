/**
 * Description: Decomposes graph into 2-edge-connected components and builds a bridge tree of them.
 * Note that if there are multiple edges between the same pair, you have to assign each edge an id instead of checking if v equals the parent in the DFS.
 * Source: self
 * Verification: https://codeforces.com/gym/100676 (problem H), https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-queries-on-the-graph/problem
 * Time: O(n + m)
 */

struct BridgeTree {
    int n, ti;
    vector<int> num, id, stk;
    vector<vector<int>> adj, tree, comp;

    BridgeTree(int _n) : n(_n), ti(0), num(n), id(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
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
                for (int v : adj[u])
                    if (id[u] != id[v])
                        tree[id[u]].push_back(id[v]);
    }

    int dfs(int u, int p) {
        int low = num[u] = ++ti;
        stk.push_back(u);
        for (int v : adj[u])
            if (v != p) {
                if (!num[v]) {
                    int ret = dfs(v, u);
                    low = min(low, ret);
                    if (num[u] < ret) {
                        comp.emplace_back();
                        while (comp.back().empty() || comp.back().back() != v) {
                            id[stk.back()] = (int) comp.size() - 1;
                            comp.back().push_back(stk.back());
                            stk.pop_back();
                        }
                    }
                } else {
                    low = min(low, num[v]);
                }
            }
        return low;
    }
};
