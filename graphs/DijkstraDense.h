/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Better for dense graphs.
 * Source: https://cp-algorithms.com/graph/dijkstra.html
 * Verification: https://www.spoj.com/problems/EZDIJKST/
 * Time: O(n^2)
 */

#define MAXN 100

int n, dist[MAXN];
bool visited[MAXN];
vector<pair<int, int>> adj[MAXN];

void dijkstra(int s) {
    memset(dist, 127, sizeof(dist));
    memset(visited, false, sizeof(visited));
    dist[s] = 0;
    for (int i=0; i<n; i++) {
        int u = -1;
        for (int v=0; v<n; v++)
            if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                u = v;

        visited[u] = true;
        for (auto e : adj[u])
            if (dist[u] + e.second < dist[e.first])
                dist[e.first] = dist[u] + e.second;
    }
}
