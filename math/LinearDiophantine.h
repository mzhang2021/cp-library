/**
 * Description: Solves a linear diophantine equation via the extended Euclidean algorithm. Once a solution (x0, y0) is found, x = x0 + k * b / gcd, y = y0 - k * a / gcd.
 * Source: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
 * Verification: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1031
 * Time: O(log n)
 */

int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return d;
}

bool solve(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(a, b, x0, y0);
    if (c % g)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    return true;
}
