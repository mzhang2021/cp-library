// Source: https://codeforces.com/blog/entry/98782

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 2e5 + 14, inf = 1e9;
int sweep_line_x = -1e8;
const double EPS = 1e-9;

struct Circle {
    int x, y, r;

    double get_y(bool up_side) const {
        int b = -2 * y;
        ll c = (ll) y * y + (sweep_line_x - x) * ll(sweep_line_x - x) - (ll) r * r;
        ll delta = b * (ll) b - 4 * c;
        return (-b + (up_side ? sqrt(delta) : -sqrt(delta))) / 2;
    }
};

struct Curve {
    bool up_side;
    Circle circle;

    bool operator<(const Curve &rhs) const {
        return circle.get_y(up_side) + EPS < rhs.circle.get_y(rhs.up_side);
    }
};

struct Interval {
    int owner_id;
    Curve up, down;

    bool operator<(const Interval &rhs) const {
        return down < rhs.down || up < rhs.up;
    }

    bool operator==(const Interval &rhs) const {
        return !(*this < rhs) && !(rhs < *this);
    }
};

int n;
Circle circle[maxn];
vector<int> g[maxn];

int main() {
    cin >> n;
    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        cin >> circle[i].x >> circle[i].y >> circle[i].r;
        events.emplace_back(circle[i].x - circle[i].r, i);
        events.emplace_back(circle[i].x + circle[i].r, i);
    }
    sort(events.begin(), events.end());
    circle[0] = {0, 0, inf};
    set<Interval> intervals({{0, {true, circle[0]}, {false, circle[0]}}});
    for (auto tmp : events) {
        int sw_x = tmp.first, circle_id = tmp.second;
        sweep_line_x = sw_x;
        int x = circle[circle_id].x, r = circle[circle_id].r;
        Interval inside = {circle_id, {true, circle[circle_id]}, {false, circle[circle_id]}};
        if (sw_x == x - r) {
            auto par_it = --intervals.lower_bound(inside);
            auto par_interval = *par_it;
            intervals.erase(par_it);
            g[par_interval.owner_id].push_back(circle_id);
            auto up_interval = par_interval, down_interval = par_interval;
            up_interval.down = {true, circle[circle_id]};
            down_interval.up = {false, circle[circle_id]};
            intervals.insert(up_interval);
            intervals.insert(down_interval);
            intervals.insert(inside);
        } else {
            auto me = intervals.lower_bound(inside);
            auto joined = *prev(me);
            joined.up = next(me)->up;
            intervals.erase(prev(me));
            intervals.erase(next(me));
            intervals.erase(me);
            intervals.insert(joined);
        }
    }
    for (int i = 0; i <= n; ++i)
        for (auto child : g[i])
            cout << i << ' ' << child << '\n';
}
