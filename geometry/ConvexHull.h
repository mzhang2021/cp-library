/**
 * Description: Finds the convex hull of a set of points via Andrew's Monotone Chain Algorithm. Change <= to < to allow points on the edges.
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Verification: https://open.kattis.com/problems/convexhull
 * Time: O(n log n)
 */

#include "Point.h"

template<typename T>
vector<Point<T>> convexHull(vector<Point<T>> &p) {
    sort(p.begin(), p.end());
    vector<Point<T>> h;
    h.reserve(p.size() + 1);
    for (int rep=0; rep<2; rep++) {
        auto start = h.size();
        for (auto pt : p) {
            while (h.size() >= start + 2 && ccw(h[h.size()-2], h.back(), pt) <= 0)
                h.pop_back();
            h.push_back(pt);
        }
        h.pop_back();
        reverse(p.begin(), p.end());
    }
    return h;
}
