/**
 * Description: Finds the correct order of traversal for a DAG.
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=1017
 * Time: O(n + m)
 */

#define MAXN 100000

bool visited[MAXN];
vector<int> adj[MAXN];
stack<int> st;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v);
    st.push(u);
}

void topSort() {
    int n;
    memset(visited, false, sizeof(visited));
    for (int i=0; i<n; i++)
        if (!visited[i])
            dfs(i);
}
