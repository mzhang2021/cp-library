/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Better for sparse graphs.
 * Source: own
 * Verification: http://codeforces.com/problemset/problem/20/C
 * Time: O(m log n)
 */

#define MAXN 100000

int dist[MAXN];
vector<pair<int, int>> adj[MAXN];

void dijkstra(int s) {
    memset(dist, 127, sizeof(dist));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        if (p.first > dist[p.second])
            continue;

        for (auto e : adj[p.second])
            if (p.first + e.second < dist[e.first]) {
                dist[e.first] = p.first + e.second;
                pq.push({dist[e.first], e.first});
            }
    }
}
