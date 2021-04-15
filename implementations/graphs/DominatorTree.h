/**
 * Description: Builds the dominator tree, where u dominates v if u is an ancestor of v. u dominates v if u is on every path from the root to v.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Advanced/DominatorTree.h, https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
 * Verification: https://cses.fi/problemset/task/1703
 * Time: O((n + m) log n)
 */

struct DominatorTree {
    int ti;
    vector<int> label, rlabel, dom, sdom, par, best;
    vector<vector<int>> adj, radj, children, bucket, tree;

    DominatorTree(int n) : ti(0), label(n, -1), rlabel(n), dom(n), sdom(n), par(n), best(n), adj(n), radj(n), children(n), bucket(n), tree(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void init(int r = 0) {
        dfs(r);
        for (int u=ti-1; u>=0; u--) {
            for (int v : radj[u])
                sdom[u] = min(sdom[u], sdom[find(v)]);
            if (u > 0)
                bucket[sdom[u]].push_back(u);
            for (int v : bucket[u]) {
                int w = find(v);
                dom[v] = sdom[v] == sdom[w] ? sdom[v] : w;
            }
            for (int v : children[u])
                par[v] = u;
        }
        for (int u=1; u<ti; u++) {
            if (dom[u] != sdom[u])
                dom[u] = dom[dom[u]];
            tree[rlabel[dom[u]]].push_back(rlabel[u]);
        }
    }

    void dfs(int u) {
        label[u] = ti;
        rlabel[ti] = u;
        sdom[ti] = par[ti] = best[ti] = ti;
        ti++;
        for (int v : adj[u]) {
            if (label[v] == -1) {
                dfs(v);
                children[label[u]].push_back(label[v]);
            }
            radj[label[v]].push_back(label[u]);
        }
    }

    int find(int u) {
        if (par[u] != u) {
            int v = find(par[u]);
            par[u] = par[par[u]];
            if (sdom[v] < sdom[best[u]])
                best[u] = v;
        }
        return best[u];
    }
};
