/**
 * Description: Solves the single source shortest path problem for graphs with negative edges.
 * Source: Competitive Programming 3
 * Verification: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=499
 * Time: O(n * m)
 */

#define MAXN 100

int n, dist[MAXN];
vector<pair<int, int>> adj[MAXN];

bool bellmanFord(int s) {
    memset(dist, 127, sizeof(dist));
    dist[s] = 0;
    bool cycle;
    for (int i=0; i<n; i++) {
        cycle = false;
        for (int u=0; u<n; u++)
            for (auto e : adj[u])
                if (dist[u] + e.second < dist[e.first]) {
                    dist[e.first] = dist[u] + e.second;
                    cycle = true;
                }
    }
    return cycle;
}
