/**
 * Description: Decomposes graph into strongly connected components.
 * Source: Competitive Programming 3
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=516
 * Time: O(n + m)
 */

#define MAXN 100000

int n, id, sccCount, dfsNum[MAXN], dfsLow[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN];
stack<int> s;

void dfs(int u) {
    dfsNum[u] = dfsLow[u] = id++;
    s.push(u);
    visited[u] = true;
    for (int v : adj[u]) {
        if (dfsNum[v] == -1)
            dfs(v);
        if (visited[v])
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
    }

    if (dfsLow[u] == dfsNum[u]) {
        int v = -1;
        while (u != v) {
            v = s.top();
            s.pop();
            visited[v] = false;
        }
        sccCount++;
    }
}

void scc() {
    memset(dfsNum, -1, sizeof(dfsNum));
    id = sccCount = 0;
    for (int i=0; i<n; i++)
        if (dfsNum[i] == -1)
            dfs(i);
}
