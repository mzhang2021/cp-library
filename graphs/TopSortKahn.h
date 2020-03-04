/**
 * Description: Finds the correct order of traversal for a DAG.
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=1017
 * Time: O(n + m)
 */

#define MAXN 100000

int indegree[MAXN];
vector<int> adj[MAXN];

void topSort() {
    int n;
    memset(indegree, 0, sizeof(indegree));
    for (int i=0; i<n; i++)
        for (int v : adj[i])
            indegree[v]++;

    queue<int> q;
    for (int i=0; i<n; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // do something with the node
        for (int v : adj[u])
            if (--indegree[v] == 0)
                q.push(v);
    }
}

