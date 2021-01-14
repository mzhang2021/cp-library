/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Better for sparse graphs.
 * Source: own
 * Verification: http://codeforces.com/problemset/problem/20/C
 * Time: O(m log n)
 */

const int MAXN = 100005;

int dist[MAXN];
vector<pair<int, int>> adj[MAXN];

void dijkstra(int s) {
    memset(dist, 127, sizeof(dist));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(dist[s] = 0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v])
                pq.emplace(dist[v] = dist[u] + w, v);
    }
}
