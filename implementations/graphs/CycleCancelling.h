/**
 * Description: Finds the minimum cost circulation of a flow graph with negative cycles.
 * To find the maximum flow, add a source and sink node, and add an edge from t to s with infinite capacity and negative infinity cost.
 * Source: https://community.topcoder.com/stat?c=problem_solution&rm=312044&rd=14730&pm=11217&cr=22840511
 * Verification: http://acm.hdu.edu.cn/showproblem.php?pid=4067, https://community.topcoder.com/stat?c=problem_statement&pm=11217&rd=14730&rm=312044&cr=22840511
 * Time: O(F * n^2 * m)
 */

struct MCF {
    struct Edge {
        int u, v;
        long long cap, cost, flow;

        Edge(int _u, int _v, long long _cap, long long _cost) : u(_u), v(_v), cap(_cap), cost(_cost), flow(0) {}
    };

    int m, n;
    vector<int> par;
    vector<long long> dist;
    vector<bool> onStack;
    vector<Edge> edges;
    vector<vector<int>> adj;

    MCF(int _n) : m(0), n(_n), par(n), dist(n), onStack(n), adj(n) {}

    void addEdge(int u, int v, long long cap, long long cost) {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    int dfs(int u) {
        onStack[u] = true;
        for (int e : adj[u])
            if (edges[e].flow < edges[e].cap && dist[u] + edges[e].cost < dist[edges[e].v]) {
                par[edges[e].v] = e;
                dist[edges[e].v] = dist[u] + edges[e].cost;
                if (onStack[edges[e].v])
                    return edges[e].v;
                int ret = dfs(edges[e].v);
                if (ret != -1)
                    return ret;
            }
        onStack[u] = false;
        return -1;
    }

    long long solve() {
        long long ret = 0;
        while (true) {
            fill(dist.begin(), dist.end(), 0);
            fill(onStack.begin(), onStack.end(), false);
            int s = -1;
            for (int u=0; u<n; u++) {
                s = dfs(u);
                if (s != -1)
                    break;
            }
            if (s == -1)
                break;
            int u = s;
            long long f = LLONG_MAX;
            do {
                f = min(f, edges[par[u]].cap - edges[par[u]].flow);
                u = edges[par[u]].u;
            } while (u != s);
            do {
                edges[par[u]].flow += f;
                edges[par[u] ^ 1].flow -= f;
                ret += f * edges[par[u]].cost;
                u = edges[par[u]].u;
            } while (u != s);
        }
        return ret;
    }
};
