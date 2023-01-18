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
    vector<pair<int, int>> edges;
    vector<vector<int>> tree, ecomp, vcomp;
    vector<vector<pair<int, int>>> adj;

    BCC(int _n) : n(_n), ti(0), num(n), id(n), art(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, edges.size());
        adj[v].emplace_back(u, edges.size());
        edges.emplace_back(u, v);
    }

    void init(bool buildTree = false) {
        for (int u=0; u<n; u++)
            if (!num[u])
                dfs(u, -1);
        if (buildTree) {
            for (const auto &v : ecomp) {
                vcomp.emplace_back();
                for (int e : v) {
                    vcomp.back().push_back(edges[e].first);
                    vcomp.back().push_back(edges[e].second);
                }
                sort(vcomp.back().begin(), vcomp.back().end());
                vcomp.back().erase(unique(vcomp.back().begin(), vcomp.back().end()), vcomp.back().end());
            }
            tree.resize(vcomp.size());
            for (int u=0; u<n; u++)
                if (art[u]) {
                    id[u] = (int) tree.size();
                    tree.emplace_back();
                }
            for (int i=0; i<(int)vcomp.size(); i++)
                for (int u : vcomp[i]) {
                    if (art[u]) {
                        tree[id[u]].push_back(i);
                        tree[i].push_back(id[u]);
                    } else {
                        id[u] = i;
                    }
                }
        }
    }

    int dfs(int u, int p) {
        int low = num[u] = ++ti;
        for (auto [v, i] : adj[u])
            if (i != p) {
                if (!num[v]) {
                    stk.push_back(i);
                    int ret = dfs(v, i);
                    low = min(low, ret);
                    if (num[u] <= ret) {
                        art[u] = p != -1 || num[v] > num[u] + 1;
                        ecomp.emplace_back();
                        while (true) {
                            int e = stk.back();
                            stk.pop_back();
                            ecomp.back().push_back(e);
                            if (e == i)
                                break;
                        }
                    }
                } else if (num[u] > num[v]) {
                    low = min(low, num[v]);
                    stk.push_back(i);
                }
            }
        return low;
    }
};
