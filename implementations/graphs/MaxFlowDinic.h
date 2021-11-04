/**
 * Description: Finds the maximum flow of a graph. Faster than Edmonds Karp.
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Verification: https://www.spoj.com/problems/FASTFLOW/
 * Time: O(n^2 * m)
 */

struct Dinic {
    struct Edge {
        int u, v;
        long long cap, flow;

        Edge(int _u, int _v, long long _cap) : u(_u), v(_v), cap(_cap), flow(0) {}
    };

    int m, s, t;
    vector<int> level, ptr;
    vector<Edge> edges;
    vector<vector<int>> adj;

    Dinic(int n, int _s, int _t) : m(0), s(_s), t(_t), level(n), ptr(n), adj(n) {}

    void addEdge(int u, int v, long long cap, long long rcap = 0) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, rcap);
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int e : adj[u])
                if (edges[e].flow < edges[e].cap && level[edges[e].v] == -1) {
                    level[edges[e].v] = level[u] + 1;
                    q.push(edges[e].v);
                }
        }
        return level[t] != -1;
    }

    long long dfs(int u, long long f) {
        if (f == 0 || u == t)
            return f;
        while (ptr[u] < (int) adj[u].size()) {
            int e = adj[u][ptr[u]], v = edges[e].v;
            long long nf;
            if (level[u] + 1 == level[v] && edges[e].flow < edges[e].cap && (nf = dfs(v, min(f, edges[e].cap - edges[e].flow))) > 0) {
                edges[e].flow += nf;
                edges[e^1].flow -= nf;
                return nf;
            }
            ptr[u]++;
        }
        return 0;
    }

    long long maxFlow(long long limit = LLONG_MAX) {
        long long ret = 0;
        while (limit > 0 && bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long f = dfs(s, limit)) {
                ret += f;
                limit -= f;
            }
        }
        return ret;
    }
};
