/**
 * Description: Finds the minimum cost maximum flow of a graph. Allows negative cost edges, but not negative cost cycles.
 * Source: https://usaco.guide/adv/min-cost-flow?lang=cpp, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/MCMF_2.h
 * Verification: https://cses.fi/problemset/task/2121/
 * Time: O(F * m * log m)
 */

struct Edge {
    int u, v;
    long long cap, cost, flow;

    Edge(int _u, int _v, long long _cap, long long _cost) : u(_u), v(_v), cap(_cap), cost(_cost), flow(0) {}
};

struct MCMF {
    int m, n, s, t;
    vector<int> par;
    vector<long long> pi, dist;
    vector<Edge> edges;
    vector<vector<int>> adj;

    MCMF(int _n, int _s, int _t) : m(0), n(_n), s(_s), t(_t), par(n), pi(n), dist(n), adj(n) {}

    void addEdge(int u, int v, long long cap, long long cost) {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    bool path() {
        fill(dist.begin(), dist.end(), LLONG_MAX);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.emplace(dist[s] = 0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u])
                continue;
            for (int e : adj[u])
                if (edges[e].flow < edges[e].cap && dist[u] + edges[e].cost + pi[u] - pi[edges[e].v] < dist[edges[e].v]) {
                    par[edges[e].v] = e;
                    pq.emplace(dist[edges[e].v] = dist[u] + edges[e].cost + pi[u] - pi[edges[e].v], edges[e].v);
                }
        }
        return dist[t] < LLONG_MAX;
    }

    void setpi() {
        fill(pi.begin(), pi.end(), LLONG_MAX);
        pi[s] = 0;
        bool cycle;
        for (int i=0; i<n; i++) {
            cycle = false;
            for (const Edge &e : edges)
                if (e.cap > 0 && pi[e.u] < LLONG_MAX && pi[e.u] + e.cost < pi[e.v]) {
                    pi[e.v] = pi[e.u] + e.cost;
                    cycle = true;
                }
        }
        assert(!cycle);
    }

    pair<long long, long long> maxFlow(long long limit = LLONG_MAX) {
        setpi();
        long long retFlow = 0, retCost = 0;
        while (limit > 0 && path()) {
            for (int u=0; u<n; u++)
                pi[u] += dist[u];
            long long f = limit;
            for (int u=t; u!=s; u=edges[par[u]].u)
                f = min(f, edges[par[u]].cap - edges[par[u]].flow);
            retFlow += f;
            retCost += f * (pi[t] - pi[s]);
            limit -= f;
            for (int u=t; u!=s; u=edges[par[u]].u) {
                edges[par[u]].flow += f;
                edges[par[u] ^ 1].flow -= f;
            }
        }
        return {retFlow, retCost};
    }
};
