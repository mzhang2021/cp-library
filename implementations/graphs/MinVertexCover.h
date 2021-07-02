/**
 * Description: Finds a minimum vertex cover of a bipartite graph based on a maximum matching.
 * Source: https://ali-ibrahim137.github.io/competitive/programming/2020/01/02/maximum-independent-set-in-bipartite-graphs.html
 * Verification: https://cses.fi/problemset/task/1709
 * Time: O(n + m)
 */

#include "MatchingHopcroftKarp.h"

void mvc(int n, int m, const Matching &matching) {
    vector<bool> visL(n + 1), visR(m + 1);

    auto dfs = [&] (auto &self, int u) -> void {
        visL[u] = true;
        for (int v : matching.adj[u])
            if (v != matching.matchL[u] && !visR[v]) {
                visR[v] = true;
                if (matching.matchR[v] && !visL[matching.matchR[v]])
                    self(self, matching.matchR[v]);
            }
    };

    for (int u=1; u<=n; u++)
        if (!matching.matchL[u])
            dfs(dfs, u);

    // MVC consists of !visL[u] and visR[v]
    // MIS is the complement of the MVC
}
