/**
 * Description: Finds the minimum spanning tree of a graph. Better for sparse graphs.
 * Source: Competitive Programming 3
 * Verification: https://www.spoj.com/problems/MARYBMW/
 * Time: O(m log n)
 */

#define MAXN 100000

bool visited[MAXN];
vector<pair<int, int>> adj[MAXN];

int prim(int s) {
    memset(visited, false, sizeof(visited));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int ret = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        if (visited[p.second])
            continue;

        ret += p.first;
        visited[p.second] = true;
        for (auto e : adj[p.second])
            if (!visited[e.first])
                pq.push({e.second, e.first});
    }
    return ret;
}
