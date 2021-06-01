/**
 * Description: Finds a valid Euler tour of a graph. Prerequisite is that there are either zero or two nodes with odd degree.
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/EulerWalk.h
 * Verification: https://www.spoj.com/problems/WORDS1/
 * Time: O(n + m)
 */

#define MAXN 100000

int n, m, degree[MAXN], pos[MAXN];
bool visited[MAXN];
vector<pair<int, int>> adj[MAXN];

vector<int> eulerPath(int s) {
    memset(degree, 0, sizeof(degree));
    memset(pos, 0, sizeof(pos));
    memset(visited, false, sizeof(visited));

    vector<int> ret;
    stack<int> st;
    st.push(s);
    degree[s]++;    // comment out to find tour instead of path
    while (!st.empty()) {
        int u = st.top();
        if (pos[u] == (int) adj[u].size()) {
            ret.push_back(u);
            st.pop();
            continue;
        }

        auto e = adj[u][pos[u]++];
        if (!visited[e.second]) {
            st.push(e.first);
            degree[u]--;
            degree[e.first]++;
            visited[e.second] = true;
        }
    }

    for (int i=0; i<n; i++)
        if (degree[i] < 0 || (int) ret.size() < m + 1)
            return {};
    return {ret.rbegin(), ret.rend()};
}
