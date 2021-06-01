/**
 * Description: Finds a maximum bipartite matching for a bipartite graph. Faster than naive DFS algorithm. Vertices are one-indexed.
 * To recover the matching, use vector matchL. To recover maximum independent set or minimum vertex cover, refer to other file.
 * Source: https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
 * Verification: https://www.spoj.com/problems/MATCHING/, https://cses.fi/problemset/task/1709
 * Time: O(sqrt(n) * m)
 */

struct Matching {
    int n, m;
    vector<int> matchL, matchR, dist;
    vector<vector<int>> adj;

    Matching(int _n, int _m) : n(_n), m(_m), matchL(n + 1), matchR(m + 1), dist(n + 1), adj(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u=1; u<=n; u++) {
            if (!matchL[u]) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
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

    int solve() {
        int ret = 0;
        while (bfs())
            for (int u=1; u<=n; u++)
                if (!matchL[u] && dfs(u))
                    ret++;
        return ret;
    }
};
