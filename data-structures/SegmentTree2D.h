/**
 * Description: Performs 2D range queries and point updates.
 * Source: https://cp-algorithms.com/data_structures/segment_tree.html
 * Verification: self
 * Time: O(log^2 n) query and update
 */

#define MAXN 1005

int n, m, st[4*MAXN][4*MAXN], a[MAXN][MAXN];

void build_y(int px, int lx, int rx, int py, int ly, int ry) {
    if (ly == ry) {
        st[px][py] = (lx == rx ? a[lx][ly] : st[2*px][py] + st[2*px+1][py]);
        return;
    }
    int my = (ly + ry) / 2;
    build_y(px, lx, rx, 2*py, ly, my);
    build_y(px, lx, rx, 2*py+1, my+1, ry);
    st[px][py] = st[px][2*py] + st[px][2*py+1];
}

void build_x(int px, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build_x(2*px, lx, mx);
        build_x(2*px+1, mx+1, rx);
    }
    build_y(px, lx, rx, 1, 0, m-1);
}

int query_y(int px, int py, int ly, int ry, int iy, int jy) {
    if (iy > ry || jy < ly)
        return 0;
    if (iy <= ly && ry <= jy)
        return st[px][py];
    int my = (ly + ry) / 2;
    return query_y(px, 2*py, ly, my, iy, jy) + query_y(px, 2*py+1, my+1, ry, iy, jy);
}

int query_x(int px, int lx, int rx, int ix, int iy, int jx, int jy) {
    if (ix > rx || jx < lx)
        return 0;
    if (ix <= lx && rx <= jx)
        return query_y(px, 1, 0, m-1, iy, jy);
    int mx = (lx + rx) / 2;
    return query_x(2*px, lx, mx, ix, iy, jx, jy) + query_x(2*px+1, mx+1, rx, ix, iy, jx, jy);
}

void update_y(int px, int lx, int rx, int py, int ly, int ry, int y, int val) {
    if (ly == ry) {
        st[px][py] = (lx == rx ? val : st[2*px][py] + st[2*px+1][py]);
        return;
    }
    int my = (ly + ry) / 2;
    if (y <= my)
        update_y(px, lx, rx, 2*py, ly, my, y, val);
    else
        update_y(px, lx, rx, 2*py+1, my+1, ry, y, val);
    st[px][py] = st[px][2*py] + st[px][2*py+1];
}

void update_x(int px, int lx, int rx, int x, int y, int val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x(2*px, lx, mx, x, y, val);
        else
            update_x(2*px+1, mx+1, rx, x, y, val);
    }
    update_y(px, lx, rx, 1, 0, m-1, y, val);
}
