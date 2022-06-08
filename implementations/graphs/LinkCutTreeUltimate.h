/**
 * Description: The ultimate link cut tree supporting all path/subtree lazy updates and aggregates. Also known as AAA tree. Nodes are 1-indexed.
 * Note that lazy style is different from my usual style, lazy on node means value is already updated instead of pending update.
 * Only modifications required are: 1. Data struct, 2. Set MAX to 2n, 3. Populate freeList with n nodes at the start.
 * Source: https://www.cnblogs.com/clrs97/p/4403244.html
 * Verification: https://dmoj.ca/problem/ds5
 * Time: O(log n)
 */

const int MAX = 2e5 + 5;

struct Data {
    int sum, mn, mx, sz;

    Data() : sum(0), mn(INT_MAX), mx(INT_MIN), sz(0) {}

    Data(int val) : sum(val), mn(val), mx(val), sz(1) {}

    Data(int _sum, int _mn, int _mx, int _sz) : sum(_sum), mn(_mn), mx(_mx), sz(_sz) {}
};

struct Lazy {
    int a, b;

    Lazy(int _a = 1, int _b = 0) : a(_a), b(_b) {}

    bool lazy() {
        return a != 1 || b != 0;
    }
};

Data operator + (const Data &a, const Data &b) {
    return Data(a.sum + b.sum, min(a.mn, b.mn), max(a.mx, b.mx), a.sz + b.sz);
}

Data& operator += (Data &a, const Data &b) {
    return a = a + b;
}

Lazy& operator += (Lazy &a, const Lazy &b) {
    return a = Lazy(a.a * b.a, a.b * b.a + b.b);
}

int& operator += (int &a, const Lazy &b) {
    return a = a * b.a + b.b;
}

Data& operator += (Data &a, const Lazy &b) {
    return a.sz ? a = Data(a.sum * b.a + a.sz * b.b, a.mn * b.a + b.b, a.mx * b.a + b.b, a.sz) : a;
}

struct Node {
    int p, ch[4], val;
    Data path, sub, all;
    Lazy plazy, slazy;
    bool flip, fake;

    Node() : p(0), ch(), path(), sub(), all(), plazy(), slazy(), flip(false), fake(true) {}

    Node(int _val) : Node() {
        val = _val;
        path = all = Data(val);
        fake = false;
    }
} tr[MAX];
vector<int> freeList;

void pushFlip(int u) {
    if (!u)
        return;
    swap(tr[u].ch[0], tr[u].ch[1]);
    tr[u].flip ^= true;
}

void pushPath(int u, const Lazy &lazy) {
    if (!u || tr[u].fake)
        return;
    tr[u].val += lazy;
    tr[u].path += lazy;
    tr[u].all = tr[u].path + tr[u].sub;
    tr[u].plazy += lazy;
}

void pushSub(int u, bool o, const Lazy &lazy) {
    if (!u)
        return;
    tr[u].sub += lazy;
    tr[u].slazy += lazy;
    if (!tr[u].fake && o)
        pushPath(u, lazy);
    else
        tr[u].all = tr[u].path + tr[u].sub;
}

void push(int u) {
    if (!u)
        return;
    if (tr[u].flip) {
        pushFlip(tr[u].ch[0]);
        pushFlip(tr[u].ch[1]);
        tr[u].flip = false;
    }
    if (tr[u].plazy.lazy()) {
        pushPath(tr[u].ch[0], tr[u].plazy);
        pushPath(tr[u].ch[1], tr[u].plazy);
        tr[u].plazy = Lazy();
    }
    if (tr[u].slazy.lazy()) {
        pushSub(tr[u].ch[0], false, tr[u].slazy);
        pushSub(tr[u].ch[1], false, tr[u].slazy);
        pushSub(tr[u].ch[2], true, tr[u].slazy);
        pushSub(tr[u].ch[3], true, tr[u].slazy);
        tr[u].slazy = Lazy();
    }
}

void pull(int u) {
    if (!tr[u].fake)
        tr[u].path = tr[tr[u].ch[0]].path + tr[tr[u].ch[1]].path + tr[u].val;
    tr[u].sub = tr[tr[u].ch[0]].sub + tr[tr[u].ch[1]].sub + tr[tr[u].ch[2]].all + tr[tr[u].ch[3]].all;
    tr[u].all = tr[u].path + tr[u].sub;
}

void attach(int u, int d, int v) {
    tr[u].ch[d] = v;
    tr[v].p = u;
    pull(u);
}

int dir(int u, int o) {
    int v = tr[u].p;
    return tr[v].ch[o] == u ? o : tr[v].ch[o+1] == u ? o + 1 : -1;
}

void rotate(int u, int o) {
    int v = tr[u].p, w = tr[v].p, du = dir(u, o), dv = dir(v, o);
    if (dv == -1 && o == 0)
        dv = dir(v, 2);
    attach(v, du, tr[u].ch[du^1]);
    attach(u, du ^ 1, v);
    if (~dv)
        attach(w, dv, u);
    else
        tr[u].p = w;
}

void splay(int u, int o) {
    push(u);
    while (~dir(u, o) && (o == 0 || tr[tr[u].p].fake)) {
        int v = tr[u].p, w = tr[v].p;
        push(w);
        push(v);
        push(u);
        int du = dir(u, o), dv = dir(v, o);
        if (~dv && (o == 0 || tr[w].fake))
            rotate(du == dv ? v : u, o);
        rotate(u, o);
    }
}

void add(int u, int v) {
    if (!v)
        return;
    for (int i=2; i<4; i++)
        if (!tr[u].ch[i]) {
            attach(u, i, v);
            return;
        }
    int w = freeList.back();
    freeList.pop_back();
    attach(w, 2, tr[u].ch[2]);
    attach(w, 3, v);
    attach(u, 2, w);
}

void recPush(int u) {
    if (tr[u].fake)
        recPush(tr[u].p);
    push(u);
}

void rem(int u) {
    int v = tr[u].p;
    recPush(v);
    if (tr[v].fake) {
        int w = tr[v].p;
        attach(w, dir(v, 2), tr[v].ch[dir(u, 2) ^ 1]);
        if (tr[w].fake)
            splay(w, 2);
        freeList.push_back(v);
    } else {
        attach(v, dir(u, 2), 0);
    }
    tr[u].p = 0;
}

int par(int u) {
    int v = tr[u].p;
    if (!tr[v].fake)
        return v;
    splay(v, 2);
    return tr[v].p;
}

int access(int u) {
    int v = u;
    splay(u, 0);
    add(u, tr[u].ch[1]);
    attach(u, 1, 0);
    while (tr[u].p) {
        v = par(u);
        splay(v, 0);
        rem(u);
        add(v, tr[v].ch[1]);
        attach(v, 1, u);
        splay(u, 0);
    }
    return v;
}

void reroot(int u) {
    access(u);
    pushFlip(u);
}

void link(int u, int v) {
    reroot(u);
    access(v);
    add(v, u);
}

void cut(int u, int v) {
    reroot(u);
    access(v);
    tr[v].ch[0] = tr[u].p = 0;
    pull(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i=0; i<n-1; i++) {
        int x, y;
        cin >> x >> y;
        edges.emplace_back(x, y);
    }

    for (int i=1; i<=n; i++) {
        int w;
        cin >> w;
        tr[i] = Node(w);
    }
    for (int i=n+1; i<MAX; i++)
        freeList.push_back(i);
    for (auto [x, y] : edges)
        link(x, y);

    int rt;
    cin >> rt;
    while (m--) {
        int k;
        cin >> k;
        if (k == 1) {   // change root
            cin >> rt;
        } else if (k == 3 || k == 4 || k == 11) {   // subtree query
            int x;
            cin >> x;
            reroot(rt);
            access(x);
            Data ret = tr[x].val;
            for (int i=2; i<4; i++)
                ret += tr[tr[x].ch[i]].all;
            if (k == 3)
                cout << ret.mn << "\n";
            else if (k == 4)
                cout << ret.mx << "\n";
            else
                cout << ret.sum << "\n";
        } else if (k == 0 || k == 5) {  // subtree update
            int x, y;
            cin >> x >> y;
            reroot(rt);
            access(x);
            Lazy lazy(k == 5, y);
            tr[x].val += lazy;
            for (int i=2; i<4; i++)
                pushSub(tr[x].ch[i], true, lazy);
        } else if (k == 7 || k == 8 || k == 10) {   // path query
            int x, y;
            cin >> x >> y;
            reroot(x);
            access(y);
            Data ret = tr[y].path;
            if (k == 7)
                cout << ret.mn << "\n";
            else if (k == 8)
                cout << ret.mx << "\n";
            else
                cout << ret.sum << "\n";
        } else if (k == 2 || k == 6) {  // path update
            int x, y, z;
            cin >> x >> y >> z;
            reroot(x);
            access(y);
            pushPath(y, Lazy(k == 6, z));
        } else {    // change parent
            int x, y;
            cin >> x >> y;
            reroot(rt);
            access(y);
            if (access(x) != x) {
                tr[x].ch[0] = tr[tr[x].ch[0]].p = 0;
                pull(x);
                access(y);
                add(y, x);
            }
        }
    }

    return 0;
}
