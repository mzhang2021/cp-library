/**
 * Description: Sorts vectors radially based on angles [0, 2pi). For parallel vectors, order is arbitrary.
 * DO NOT INCLUDE (0, 0)!!!
 * Source: https://codeforces.com/blog/entry/72815
 * Verification: https://open.kattis.com/problems/leylines
 * Time: O(1)
 */

#include "Point.h"

template<typename T>
bool half(const Point<T> &p) {
    return p.y < 0 || (p.y == 0 && p.x < 0);
}

template<typename T>
bool cmp(const Point<T> &p, const Point<T> &q) {
    return half(p) == half(q) ? cross(p, q) > 0 : half(p) < half(q);
}
