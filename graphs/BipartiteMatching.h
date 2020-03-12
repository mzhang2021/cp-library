/**
 * Description: Finds a maximum bipartite matching for a bipartite graph.
 * Source: Competitive Programming 3
 * Verification: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2079
 * Time: O(n * m)
 */

#define MAXN 100

int n, match[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN];

int aug(int u) {
    if (visited[u])
        return 0;
    visited[u] = true;
    for (int v : adj[u])
        if (match[v] == -1 || aug(match[v])) {
            match[v] = u;
            return 1;
        }
    return 0;
}

int mcbm() {
    int ret = 0;
    memset(match, -1, sizeof(match));
    for (int i=0; i<n; i++) {
        memset(visited, false, sizeof(visited));
        ret += aug(i);
    }
    return ret;
}
