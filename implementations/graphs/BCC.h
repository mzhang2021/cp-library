/**
 * Description: Decomposes graph into biconnected components, finds articulation points, builds block-cut tree.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/DFS/BCC%20(12.4).h, https://ideone.com/hCUME3
 * Verification: https://codeforces.com/contest/118/problem/E, https://cses.fi/problemset/task/1705/
 * Time: O(n + m)
 */

struct BCC {
    int n, ti;
    vector<int> num, id, stk;
    vector<bool> art;
    vector<vector<int>> adj, tree, comp;

    BCC(int _n) : n(_n), ti(0), num(n), id(n), art(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init() {
        for (int u=0; u<n; u++)
            if (!num[u]) {
                dfs(u, -1);
                if (num[stk.back()] == ti)
                    art[stk.back()] = true;
                stk.pop_back();
            }
        for (int u=0; u<n; u++)
            if (art[u]) {
                id[u] = (int) tree.size();
                tree.emplace_back();
            }
        for (auto &c : comp) {
            int v = (int) tree.size();
            tree.emplace_back();
            for (int u : c) {
                if (art[u]) {
                    tree[id[u]].push_back(v);
                    tree[v].push_back(id[u]);
                } else {
                    id[u] = v;
                }
            }
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
                    if (num[u] <= ret) {
                        art[u] = p != -1 || num[v] > num[u] + 1;
                        comp.push_back({u});
                        while (comp.back().back() != v) {
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
