/**
 * Description: Solves the all pairs shortest path problem.
 * Source: own
 * Verification: https://codeforces.com/contest/1196/problem/F
 * Time: O(n^3)
 */

#define MAXN 100

int n, dist[MAXN][MAXN];

void floydWarshall() {
    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
