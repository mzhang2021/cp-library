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

    // ax + by = c
    Line(T _a, T _b, T _c) : ab(_b, -_a) {
        if (_a != 0) a = b = Point<T>(_c / _a, 0);
        else if (_b != 0) a = b = Point<T>(0, _c / _b);
        else if (_c == 0) a = b = Point<T>();
        else a = b = Point<T>(numeric_limits<T>::max(), numeric_limits<T>::max());
    }

    friend bool onLine(const Point<T> &p, const Line &l) {
        if (l.a == l.b) return p == l.a;
        return cross((p - l.a), l.ab) == 0;
    }

    friend bool onSegment(const Point<T> &p, const Line &s) {
        if (s.a == s.b) return p == s.a;
        Point<T> va = s.a - p, vb = s.b - p;
        return cross(va, vb) == 0 && dot(va, vb) <= 0;
    }

    friend bool intersectLine(const Line &s, const Line &t, Point<double> &p) {
        T w = cross(s.ab, t.ab);
        if (w == 0) {
            p = Point<double>(numeric_limits<double>::max(), numeric_limits<double>::max());
            return onLine(s.a, t);
        }
        p = s.a + Point<double>(s.ab * (cross(t.a, t.ab) + cross(t.ab, s.a))) / (double) w;
        return true;
    }

    friend bool intersectSegment(const Line &s, const Line &t, Point<double> &p) {
        T w = cross(s.a - s.b, t.a - s.b), x = cross(s.a - s.b, t.b - s.b), y = cross(t.a - t.b, s.a - t.b), z = cross(t.a - t.b, s.b - t.b);
        if ((w > 0) != (x > 0) && (y > 0) != (z > 0))
            return intersectLine(s, t, p);
        if (w == 0 && onSegment(t.a, s)) {
            p = t.a;
            return true;
        }
        if (x == 0 && onSegment(t.b, s)) {
            p = t.b;
            return true;
        }
        if (y == 0 && onSegment(s.a, t)) {
            p = s.a;
            return true;
        }
        if (z == 0 && onSegment(s.b, t)) {
            p = s.b;
            return true;
        }
        return false;
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
