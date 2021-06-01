/**
 * Description: Solves the single source shortest path problem for graphs with small positive edges. Also known as Dial's algorithm.
 * Source: https://www.geeksforgeeks.org/dials-algorithm-optimized-dijkstra-for-small-range-weights/
 * Verification: https://www.spoj.com/problems/ADATRIP/
 * Time: O(n * maxW + m)
 */

#define MAXN 100000

const int maxW;
int n, dist[MAXN];
list<int>::iterator pos[MAXN];
vector<pair<int, int>> adj[MAXN];

void dijkstra(int s) {
    memset(dist, 127, sizeof(dist));
    const int INF = dist[0];

    int i = 0;
    vector<list<int>> b(n * maxW + 1);
    dist[s] = 0;
    b[0].push_back(s);
    while (i < n * maxW) {
        int u = b[i].front();
        b[i].pop_front();

        for (auto e : adj[u])
            if (dist[u] + e.second < dist[e.first]) {
                if (dist[e.first] != INF)
                    b[dist[e.first]].erase(pos[e.first]);
                dist[e.first] = dist[u] + e.second;
                b[dist[e.first]].push_front(e.first);
                pos[e.first] = b[dist[e.first]].begin();
            }

        while (i < n * maxW && b[i].empty())
            i++;
    }
}
