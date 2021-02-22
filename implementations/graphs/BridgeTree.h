/**
 * Description: Decomposes graph into 2-edge-connected components and builds a bridge tree of them.
 * Source: self
 * Verification: https://codeforces.com/gym/100676 (problem H), https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-queries-on-the-graph/problem
 * Time: O(n + m)
 */

struct BridgeTree {
    int ti;
    vector<int> num, id, stk;
    vector<vector<int>> adj, tree, comp;

    BridgeTree(int n) : ti(0), num(n), id(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int r = 0) {
        dfs(r, -1);
        comp.emplace_back();
        while (!stk.empty()) {
            id[stk.back()] = (int) comp.size() - 1;
            comp.back().push_back(stk.back());
            stk.pop_back();
        }
        tree.resize(comp.size());
        for (auto &c : comp)
            for (int u : c)
                for (int v : adj[u])
                    if (id[u] != id[v])
                        tree[id[u]].push_back(id[v]);
        for (auto &c : tree) {
            sort(c.begin(), c.end());
            c.erase(unique(c.begin(), c.end()), c.end());
        }
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
                        while (stk.back() != v) {
                            id[stk.back()] = (int) comp.size() - 1;
                            comp.back().push_back(stk.back());
                            stk.pop_back();
                        }
                        id[v] = (int) comp.size() - 1;
                        comp.back().push_back(v);
                        stk.pop_back();
                    }
                } else if (num[u] > num[v]) {
                    low = min(low, num[v]);
                }
            }
        return low;
    }
};
