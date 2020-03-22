/**
 * Description: Decomposes graph into biconnected components, finds articulation points and bridges.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/DFS/BCC%20(12.4).h
 * Verification: https://codeforces.com/contest/118/problem/E
 * Time: O(n + m)
 */

#define MAXN 100000

int n, ti, bccCount, num[MAXN], low[MAXN];
vector<pair<int, int>> adj[MAXN];
vector<vector<int>> comp;
stack<int> st;

void dfs(int u, int p = -1) {
    num[u] = low[u] = ti++;
    int numChildren = 0;
    for (auto e : adj[u])
        if (e.first != p) {
            if (num[e.first] == -1) {
                numChildren++;
                st.push(e.second);
                dfs(e.first, u);
                low[u] = min(low[u], low[e.first]);
                if ((p == -1 && numChildren > 1) || (p != -1 && num[u] <= low[e.first])) {  // <= for articulation point, < for bridge
                    vector<int> tmp;
                    while (st.top() != e.second) {
                        tmp.push_back(st.top());
                        st.pop();
                    }
                    tmp.push_back(st.top());
                    st.pop();
                    comp.push_back(tmp);
                    bccCount++;
                }
            } else if (num[e.first] < num[u]) {
                low[u] = min(low[u], num[e.first]);
                st.push(e.second);
            }
        }
}

void bcc() {
    memset(num, -1, sizeof(num));
    ti = bccCount = 0;
    for (int i=0; i<n; i++)
        if (num[i] == -1) {
            dfs(i);
            while (!st.empty()) {
                vector<int> tmp;
                while (!st.empty()) {
                    tmp.push_back(st.top());
                    st.pop();
                }
                comp.push_back(tmp);
                bccCount++;
            }
        }
}
