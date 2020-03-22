/**
 * Description: Finds the area of a polygon with the Shoelace Theorem.
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Verification: https://codeforces.com/gym/100168
 * Time: O(n)
 */

#include "Point.h"

template<typename T>
double area(const vector<Point<T>> &p) {
    int n = p.size();
    T ret = 0;
    for (int i=0; i<n; i++)
        ret += cross(p[i], p[(i+1)%n]);
    return abs(ret) / 2.0;
}
