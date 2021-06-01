/**
 * Description: Searches for a value in a sorted array in log n time.
 * Source: https://en.wikipedia.org/wiki/Binary_search_algorithm
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=594
 * Time: O(log n)
 */

#define MAXN 100000

int n, a[MAXN];

int binarySearch(int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x)
            return m;
        else if (a[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int lowerBound(int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] < x)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

int upperBound(int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] > x)
            r = m;
        else
            l = m + 1;
    }
    return l - 1;
}
