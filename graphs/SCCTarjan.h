/**
 * Description: Decomposes graph into strongly connected components.
 * Source: Competitive Programming 3
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=516
 * Time: O(n + m)
 */

#define MAXN 100000

int n, ti, sccCount, num[MAXN], low[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN];
stack<int> st;

void dfs(int u) {
    num[u] = low[u] = ti++;
    st.push(u);
    visited[u] = true;
    for (int v : adj[u]) {
        if (num[v] == -1)
            dfs(v);
        if (visited[v])
            low[u] = min(low[u], low[v]);
    }

    if (low[u] == num[u]) {
        int v = -1;
        while (u != v) {
            v = st.top();
            st.pop();
            visited[v] = false;
        }
        sccCount++;
    }
}

void scc() {
    memset(num, -1, sizeof(num));
    ti = sccCount = 0;
    for (int i=0; i<n; i++)
        if (num[i] == -1)
            dfs(i);
}
