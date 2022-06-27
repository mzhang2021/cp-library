/**
 * Description: Finds the largest rectangular area that fits in a histogram.
 * Source: https://www.youtube.com/watch?v=VNbkzsnllsU
 * Verification: https://cses.fi/problemset/task/1142
 * Time: O(n)
 */

int histogram(const vector<int> &h) {
    int n = (int) h.size(), ret = 0;
    vector<int> stk{-1};
    for (int i=0; i<n; i++) {
        while (stk.back() != -1 && h[i] <= h[stk.back()]) {
            int j = stk.back();
            stk.pop_back();
            ret = max(ret, h[j] * (i - stk.back() - 1));
        }
        stk.push_back(i);
    }
    while (stk.back() != -1) {
        int j = stk.back();
        stk.pop_back();
        ret = max(ret, h[j] * (n - stk.back() - 1));
    }
    return ret;
}
