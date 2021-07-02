/**
 * Description: Finds a minimum cost maximum matching in a weighted bipartite graph. Vertices are one-indexed.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Verification: https://open.kattis.com/problems/cordonbleu
 * Time: O(n^2 * m)
 */

long long hungarian(const vector<vector<long long>> &adj) {
    int n = (int) adj.size(), m = (int) adj[0].size();
    vector<long long> u(n), v(m);
    vector<int> match(m);
    for (int i=1; i<n; i++) {
        int w = 0;
        match[w] = i;
        vector<long long> dist(m, LLONG_MAX);
        vector<int> pred(m, -1);
        vector<bool> vis(m);
        while (match[w]) {
            vis[w] = true;
            int cur = match[w], nw = 0;
            long long delta = LLONG_MAX;
            for (int j=1; j<m; j++)
                if (!vis[j]) {
                    long long edge = adj[cur][j] - u[cur] - v[j];
                    if (edge < dist[j]) {
                        dist[j] = edge;
                        pred[j] = w;
                    }
                    if (dist[j] < delta) {
                        delta = dist[j];
                        nw = j;
                    }
                }
            for (int j=0; j<m; j++) {
                if (vis[j]) {
                    u[match[j]] += delta;
                    v[j] -= delta;
                } else {
                    dist[j] -= delta;
                }
            }
            w = nw;
        }
        while (w) {
            int nw = pred[w];
            match[w] = match[nw];
            w = nw;
        }
    }
    return -v[0];
}
