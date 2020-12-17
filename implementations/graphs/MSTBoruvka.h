/**
 * Description: Finds the minimum spanning tree of a graph.
 * Source: own
 * Verification: https://codeforces.com/contest/888/problem/G
 * Time: O(m log n)
 */

#include "DSU.h"

#define MAX 100000

int n, m;
array<int, 3> edges[MAX];
DSU<MAX> ds;

int boruvka() {
    int numComp = n, ret = 0;
    vector<int> cheapest(n);
    while (numComp > 1) {
        cheapest.assign(n, -1);
        for (int i=0; i<m; i++) {
            int u = ds.Find(edges[i][0]), v = ds.Find(edges[i][1]);
            if (u != v) {
                if (cheapest[u] == -1 || edges[i][2] < edges[cheapest[u]][2])
                    cheapest[u] = i;
                if (cheapest[v] == -1 || edges[i][2] < edges[cheapest[v]][2])
                    cheapest[v] = i;
            }
        }
        for (int i=0; i<n; i++)
            if (cheapest[i] != -1 && ds.Find(edges[cheapest[i]][0]) != ds.Find(edges[cheapest[i]][1])) {
                ds.Union(edges[cheapest[i]][0], edges[cheapest[i]][1]);
                ret += edges[cheapest[i]][2];
                numComp--;
            }
    }
    return ret;
}
