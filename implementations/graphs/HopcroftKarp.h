/**
 * Description: Finds a maximum bipartite matching for a bipartite graph. Faster than naive DFS algorithm.
 * Source: https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
 * Verification: https://www.spoj.com/problems/MATCHING/
 * Time: O(sqrt(n) * m)
 */

#define MAX 100001

int n, matchL[MAX], matchR[MAX], dist[MAX];
vector<int> adj[MAX];

bool bfs() {
    queue<int> q;
    for (int i=1; i<=n; i++) {
        if (!matchL[i]) {
            dist[i] = 0;
            q.push(i);
        } else
            dist[i] = INT_MAX;
    }
    dist[0] = INT_MAX;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[0])
            for (int v : adj[u])
                if (dist[matchR[v]] == INT_MAX) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
    }
    return dist[0] != INT_MAX;
}

bool dfs(int u) {
    if (u != 0) {
        for (int v : adj[u])
            if (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        dist[u] = INT_MAX;
        return false;
    }
    return true;
}

int mcbm() {
    int ret = 0;
    memset(matchL, 0, sizeof(matchL));
    memset(matchR, 0, sizeof(matchR));
    while (bfs())
        for (int i=1; i<=n; i++)
            if (!matchL[i] && dfs(i))
                ret++;
    return ret;
}
