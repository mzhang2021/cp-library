/**
 * Description: Performs 2D range prefix sum queries and point updates of +1 or -1. Bounds are one-indexed on [1, x][1, y]. Space is O(q log n).
 * Source: https://codeforces.com/blog/entry/52094
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=601
 * Time: O(log^2 n) query and update
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define MAXN 100000

int n;
ordered_set bit[MAXN+1];

int query(int x, int y) {
    int ret = 0;
    for (int i=x; i>0; i-=i&-i)
        ret += bit[i].order_of_key(make_pair(y+1, 0));
    return ret;
}

void add(int x, int y) {
    for (int i=x; i<=n; i+=i&-i)
        bit[i].insert(make_pair(y, x));
}

void rem(int x, int y) {
    for (int i=x; i<=n; i+=i&-i)
        bit[i].erase(make_pair(y, x));
}
