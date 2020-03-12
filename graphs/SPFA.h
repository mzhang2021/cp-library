/**
 * Description: Solves the single source shortest path problem for graphs with positive edges. Faster variant of Bellman Ford.
 * Source: https://codeforces.com/blog/entry/16221
 * Verification: https://www.spoj.com/problems/ADATRIP/
 * Time: O(m) on average, O(n * m) in worst case
 */

#define MAXN 100000

int dist[MAXN];
bool inQueue[MAXN];
vector<pair<int, int>> adj[MAXN];

void spfa(int s) {
    memset(dist, 127, sizeof(dist));
    memset(inQueue, false, sizeof(inQueue));
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inQueue[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        for (auto e : adj[u])
            if (dist[u] + e.second < dist[e.first]) {
                dist[e.first] = dist[u] + e.second;
                if (!inQueue[e.first]) {
                    q.push(e.first);
                    inQueue[e.first] = true;
                }
            }
    }
}
