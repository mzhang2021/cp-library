/**
 * Description: HLD for non commutative aggregates
 * Verification: https://www.spoj.com/problems/GSS7/
 */

template<class B>
void process(int u, int v, B op) {
    bool s = false;
    for (; root[u]!=root[v]; u=par[root[u]]) {
        if (depth[root[u]] < depth[root[v]]) {
            swap(u, v);
            s ^= true;
        }
        op(pos[root[u]], pos[u], s);
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
        s ^= true;
    }
    op(pos[u] + VAL_IN_EDGES, pos[v], !s);
}

// path
int query(int u, int v) {
    Node ls, rs;
    process(u, v, [this, &ls, &rs] (int l, int r, bool s) {
        Node cur = st.query(l, r);
        if (s) rs.pull(cur, rs);
        else ls.pull(cur, ls);
    });
    swap(ls.pref, ls.suff);
    Node ret;
    ret.pull(ls, rs);
    return ret.ans;
}
