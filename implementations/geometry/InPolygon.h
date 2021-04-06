/**
 * Description: Checks if a point lies inside a polygon.
 * Returns 0 if outside, 1 if inside, and 2 if on the boundary.
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Verification: https://cses.fi/problemset/task/2193
 * Time: O(n)
 */

#include "Line.h"

template<typename T>
int inPolygon(const vector<Point<T>> &p, const Point<T> &a) {
    int n = (int) p.size();
    bool ret = false;
    for (int i=0; i<n; i++) {
        if (onSegment(a, Line(p[i], p[(i + 1) % n])))
            return 2;
        ret ^= ((a.y >= p[(i + 1) % n].y) - (a.y >= p[i].y)) * ccw(p[i], p[(i + 1) % n], a) > 0;
    }
    return ret;
}
