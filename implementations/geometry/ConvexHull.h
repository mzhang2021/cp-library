/**
 * Description: Finds the convex hull of a set of points via Andrew's Monotone Chain Algorithm. Change <= to < to allow points on the edges.
 * Points are returned in counter-clockwise order. For a line it returns its two endpoints. Does NOT handle duplicate points correctly if you also allow points on edges.
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Verification: https://open.kattis.com/problems/convexhull
 * Time: O(n log n)
 */

#include "Point.h"

template<typename T>
vector<Point<T>> convexHull(vector<Point<T>> p) {
    if (p.size() <= 1) return p;
    sort(p.begin(), p.end());
    vector<Point<T>> h;
    for (int rep=0; rep<2; rep++) {
        auto start = h.size();
        for (const auto &pt : p) {
            while (h.size() >= start + 2 && ccw(h[h.size()-2], h.back(), pt) <= 0)
                h.pop_back();
            h.push_back(pt);
        }
        h.pop_back();
        reverse(p.begin(), p.end());
    }
    return h;
}
