/**
 * Description: Finds the minimum spanning tree of a graph. Better for dense graphs.
 * Source: https://cp-algorithms.com/graph/mst_prim.html
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=946
 * Time: O(n^2)
 */

#define MAXN 100

int n, minEdge[MAXN];
bool visited[MAXN];
vector<pair<int, int>> adj[MAXN];

int prim(int s) {
    memset(minEdge, 127, sizeof(minEdge));
    memset(visited, false, sizeof(visited));
    minEdge[s] = 0;
    int ret = 0;
    for (int i=0; i<n; i++) {
        int u = -1;
        for (int v=0; v<n; v++)
            if (!visited[v] && (u == -1 || minEdge[v] < minEdge[u]))
                u = v;

        visited[u] = true;
        ret += minEdge[u];
        for (auto e : adj[u])
            if (e.second < minEdge[e.first])
                minEdge[e.first] = e.second;
    }
    return ret;
}
