/**
 * Description: Line/segment class for geometry problems.
 * Source: https://codeforces.com/blog/entry/48122
 * Verification: https://codeforces.com/gym/100168
 * Time: fast
 */

#include "Point.h"

template<typename T>
struct Line {
    Point<T> a, b, ab;

    Line() {}

    Line(const Point<T> &_a, const Point<T> &_b) : a(_a), b(_b), ab(b - a) {}

    friend bool onLine(const Point<T> &p, const Line &l) {
        if (l.a == l.b) return p == l.a;
        return cross((p - l.a), l.ab) == 0;
    }

    friend bool onSegment(const Point<T> &p, const Line &s) {
        if (s.a == s.b) return p == s.a;
        Point<T> va = s.a - p, vb = s.b - p;
        return cross(va, vb) == 0 && dot(va, vb) <= 0;
    }

    friend double distLine(const Point<T> &p, const Line &l) {
        if (l.a == l.b) return dist(p, l.a);
        return abs(cross(p - l.a, l.ab)) / l.ab.mag();
    }

    friend double distSegment(const Point<T> &p, const Line &s) {
        if (dot(p - s.a, s.ab) <= 0) return dist(p, s.a);
        if (dot(p - s.b, s.ab) >= 0) return dist(p, s.b);
        return distLine(p, s);
    }

    friend Point<T> proj(const Point<T> &p, const Line &l) {
        Point<T> ret = l.a;
        if (l.a != l.b) ret += l.ab * dot(p - l.a, l.ab) / l.ab.mag2();
        return ret;
    }

    friend Point<T> reflect(const Point<T> &p, const Line &l) {
        return proj(p, l) * 2 - p;
    }

    friend ostream& operator << (ostream &os, const Line &l) {
        return os << "<" << l.a.x << ", " << l.a.y << "> + t<" << l.ab.x << ", " << l.ab.y << ">";
    }
};
