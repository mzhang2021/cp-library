/**
 * Description: Dynamic connectivity for forests. To store aggregates on edges, add fake nodes for edges.
 * Source: https://codeforces.com/blog/entry/80383, https://codeforces.com/blog/entry/75885
 * Verification: https://www.spoj.com/problems/DYNACON1/, https://dmoj.ca/problem/ds5easy
 * Time: O(log n)
 */

struct Node {
    Node *l, *r, *par, *pp;
    bool rev;

    Node() : l(NULL), r(NULL), par(NULL), pp(NULL), rev(false) {}
};

void push(Node *u) {
    if (!u || !u->rev) return;
    swap(u->l, u->r);
    if (u->l) u->l->rev ^= true;
    if (u->r) u->r->rev ^= true;
    u->rev = false;
}

void pull(Node *u) {
    if (!u) return;
    push(u->l);
    push(u->r);
    // update aggregate values
}

void leftRotate(Node *u) {
    Node *v = u->r;
    if (v) {
        u->r = v->l;
        if (v->l) v->l->par = u;
        v->par = u->par;
    }
    if (!u->par) {
        if (v) {
            v->pp = u->pp;
            u->pp = NULL;
        }
    }
    else if (u == u->par->l) u->par->l = v;
    else u->par->r = v;
    if (v) v->l = u;
    u->par = v;
    pull(u);
    pull(v);
}

void rightRotate(Node *u) {
    Node *v = u->l;
    if (v) {
        u->l = v->r;
        if (v->r) v->r->par = u;
        v->par = u->par;
    }
    if (!u->par) {
        if (v) {
            v->pp = u->pp;
            u->pp = NULL;
        }
    }
    else if (u == u->par->l) u->par->l = v;
    else u->par->r = v;
    if (v) v->r = u;
    u->par = v;
    pull(u);
    pull(v);
}

void splay(Node *u) {
    push(u);
    while (u->par) {
        push(u->par->par);
        push(u->par);
        push(u);
        if (!u->par->par) {
            if (u->par->l == u) rightRotate(u->par);
            else leftRotate(u->par);
        } else if (u->par->l == u && u->par->par->l == u->par) {
            rightRotate(u->par->par);
            rightRotate(u->par);
        } else if (u->par->r == u && u->par->par->r == u->par) {
            leftRotate(u->par->par);
            leftRotate(u->par);
        } else if (u->par->l == u && u->par->par->r == u->par) {
            rightRotate(u->par);
            leftRotate(u->par);
        } else {
            leftRotate(u->par);
            rightRotate(u->par);
        }
    }
}

Node* access(Node *u) {
    splay(u);
    if (u->r) {
        u->r->pp = u;
        u->r->par = NULL;
        u->r = NULL;
        pull(u);
    }
    Node *v = u;
    while (u->pp) {
        v = u->pp;
        splay(v);
        if (v->r) {
            v->r->pp = v;
            v->r->par = NULL;
        }
        v->r = u;
        u->par = v;
        u->pp = NULL;
        pull(v);
        splay(u);
    }
    return v;
}

void makeRoot(Node *u) {
    access(u);
    if (u->l) u->l->rev ^= true;
    swap(u->l, u->r);
}

Node* findRoot(Node *u) {
    access(u);
    while (u->l) {
        u = u->l;
        push(u);
    }
    access(u);
    return u;
}

void link(Node *u, Node *v) {
    access(u);
    makeRoot(v);
    u->r = v;
    v->par = u;
    pull(u);
}

void cut(Node *u) {
    access(u);
    if (u->l) {
        u->l->par = NULL;
        u->l = NULL;
        pull(u);
    }
}

Node* lca(Node *u, Node *v) {
    access(u);
    return access(v);
}
