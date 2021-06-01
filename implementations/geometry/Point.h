/**
 * Description: Point/vector class for geometry problems.
 * Source: https://codeforces.com/blog/entry/48122
 * Verification: https://codeforces.com/gym/100168
 * Time: fast
 */

template<typename T>
struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    template<typename S> Point(const Point<S> &p) : x((T) p.x), y((T) p.y) {}
    Point operator + (const Point &other) const {return Point(x + other.x, y + other.y);}
    Point operator - (const Point &other) const {return Point(x - other.x, y - other.y);}
    Point operator * (T c) const {return Point(x * c, y * c);}
    Point operator / (T c) const {return Point(x / c, y / c);}
    Point& operator += (const Point &other) {return *this = *this + other;}
    Point& operator -= (const Point &other) {return *this = *this - other;}
    Point& operator *= (T c) {return *this = *this * c;}
    Point& operator /= (T c) {return *this = *this / c;}
    bool operator < (const Point &other) const {return tie(x, y) < tie(other.x, other.y);}
    bool operator <= (const Point &other) const {return tie(x, y) <= tie(other.x, other.y);}
    bool operator > (const Point &other) const {return tie(x, y) > tie(other.x, other.y);}
    bool operator >= (const Point &other) const {return tie(x, y) >= tie(other.x, other.y);}
    bool operator == (const Point &other) const {return tie(x, y) == tie(other.x, other.y);}
    bool operator != (const Point &other) const {return tie(x, y) != tie(other.x, other.y);}
    T mag2() const {return x * x + y * y;}
    double mag() const {return sqrt(mag2());}
    Point unit() const {return *this / mag();}
    Point perp() const {return Point(-y, x);}
    Point normal() const {return perp().unit();}
    double angle() const {return atan2(y, x);}
    Point rot(double ang) const {return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));}
    friend T dot(const Point &a, const Point &b) {return a.x * b.x + a.y * b.y;}
    friend T cross(const Point<T> &a, const Point<T> &b) {return a.x * b.y - a.y * b.x;}
    friend T dist2(const Point<T> &a, const Point<T> &b) {return (a - b).mag2();}
    friend double dist(const Point<T> &a, const Point<T> &b) {return (a - b).mag();}
    friend T ccw(const Point<T> &a, const Point<T> &b, const Point<T> &o) {return cross(a - o, b - o);}
    friend double angle(const Point<T> &a, const Point<T> &b) {return abs(atan2(cross(a, b), dot(a, b)));}
    friend Point<T> rot(const Point<T> &p, const Point<T> &o, double ang) {return o + (p - o).rot(ang);}
    friend ostream& operator << (ostream &os, const Point &p) {return os << "(" << p.x << ", " << p.y << ")";}
};
