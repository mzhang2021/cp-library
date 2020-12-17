/**
 * Description: Finds the minimum spanning tree of a graph.
 * Source: own
 * Verification: https://www.spoj.com/problems/MARYBMW/
 * Time: O(m log m)
 */

#include "DSU.h"

#define MAXN 100000

int n;
vector<pair<int, pair<int, int>>> edges;
DSU<MAXN> ds;

int kruskal() {
    sort(edges.begin(), edges.end());

    int ret = 0;
    ds.init(n);
    for (auto e : edges)
        if (ds.Find(e.second.first) != ds.Find(e.second.second)) {
            ds.Union(e.second.first, e.second.second);
            ret += e.first;
        }

    return ret;
}
