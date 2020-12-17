/**
 * Description: Finds the maximum flow of a graph.
 * Source: https://cp-algorithms.com/graph/edmonds_karp.html
 * Verification: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=761
 * Time: O(n * m^2)
 */

#define MAXN 100

int parent[MAXN], capacity[MAXN][MAXN];
vector<int> adj[MAXN];

int bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    parent[s] = 0;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});
    while (!q.empty()) {
        int u = q.front().first, f = q.front().second;
        q.pop();

        for (int v : adj[u])
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int nf = min(f, capacity[u][v]);
                if (v == t)
                    return nf;
                q.push({v, nf});
            }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int ret = 0;
    while (int f = bfs(s, t)) {
        ret += f;
        int v = t;
        while (v != s) {
            int u = parent[v];
            capacity[u][v] -= f;
            capacity[v][u] += f;
            v = u;
        }
    }
    return ret;
}
