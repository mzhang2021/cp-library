/**
 * Description: Reduces DP problems of finding maximum or minimum of set of lines of previous states from O(n^2) to O(n).
 * Source: https://codeforces.com/blog/entry/63823
 * Verification: https://codeforces.com/contest/1083/problem/E
 * Time: O(n)
 */

struct Line {
    long long m, c;

    long long eval(long long x) {
        return m * x + c;
    }

    bool intersect(Line &l1, Line &l2) {
        return (__int128) (c - l1.c) * (l2.m - l1.m) > (__int128) (l1.c - l2.c) * (l1.m - m);
    }
};

long long cht() {
    deque<Line> dq;
    dq.push_back({0, 0});
    long long ret = 0;
    for (int i=0; i<n; i++) {
        while (dq.size() >= 2 && dq.back().eval(x) <= dq[dq.size()-2].eval(x))
            dq.pop_back();
        long long val = dq.back().eval(x) + h * x;
        ret = max(ret, val);
        Line cur = {h, val};
        while (dq.size() >= 2 && cur.intersect(dq.front(), dq[1]))
            dq.pop_front();
        dq.push_front(cur);
    }
    return ret;
}
