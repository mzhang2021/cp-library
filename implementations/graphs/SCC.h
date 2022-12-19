/**
 * Description: Decomposes graph into strongly connected components. Component list is sorted in reverse topological sort order.
 * Source: Competitive Programming 3, https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=516
 * Time: O(n + m)
 */

struct SCC {
    int n, ti;
    vector<int> num, id, stk;
    vector<vector<int>> adj, dag, comp;

    SCC(int _n) : n(_n), ti(0), num(n), id(n, -1), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void init(bool buildDag = false) {
        for (int u=0; u<n; u++)
            if (!num[u])
                dfs(u);
        if (buildDag) {
            dag.resize(comp.size());
            for (auto &c : comp)
                for (int u : c)
                    for (int v : adj[u])
                        if (id[u] != id[v])
                            dag[id[u]].push_back(id[v]);
            for (auto &v : dag) {
                sort(v.begin(), v.end());
                v.erase(unique(v.begin(), v.end()), v.end());
            }
        }
    }

    int dfs(int u) {
        int low = num[u] = ++ti;
        stk.push_back(u);
        for (int v : adj[u]) {
            if (!num[v])
                low = min(low, dfs(v));
            else if (id[v] == -1)
                low = min(low, num[v]);
        }
        if (low == num[u]) {
            comp.emplace_back();
            do {
                id[stk.back()] = (int) comp.size() - 1;
                comp.back().push_back(stk.back());
                stk.pop_back();
            } while (comp.back().back() != u);
        }
        return low;
    }
};
