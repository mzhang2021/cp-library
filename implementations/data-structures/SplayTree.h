/**
 * Description: Binary search tree with amortized O(log n) operations
 * Source: https://codeforces.com/blog/entry/79524, https://en.wikipedia.org/wiki/Splay_tree
 * Verification: https://www.spoj.com/problems/ORDERSET/
 * Time: O(log n)
 */

template<typename T, typename Comp = less<T>>
struct SplayTree {
    int sz;
    Comp comp;

    struct Node {
        Node *l, *r, *par;
        T key;

        Node(const T &val = T()) : l(NULL), r(NULL), par(NULL), key(val) {}
    } *root;

    SplayTree() : sz(0), root(NULL) {}

    void leftRotate(Node *u) {
        Node *v = u->r;
        if (v) {
            u->r = v->l;
            if (v->l) v->l->par = u;
            v->par = u->par;
        }
        if (!u->par) root = v;
        else if (u == u->par->l) u->par->l = v;
        else u->par->r = v;
        if (v) v->l = u;
        u->par = v;
    }

    void rightRotate(Node *u) {
        Node *v = u->l;
        if (v) {
            u->l = v->r;
            if (v->r) v->r->par = u;
            v->par = u->par;
        }
        if (!u->par) root = v;
        else if (u == u->par->l) u->par->l = v;
        else u->par->r = v;
        if (v) v->r = u;
        u->par = v;
    }

    void splay(Node *u) {
        while (u->par) {
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

    Node* subtreeMin(Node *u) {
        while (u->l) u = u->l;
        return u;
    }

    Node* subtreeMax(Node *u) {
        while (u->r) u = u->r;
        return u;
    }

    void insert(const T &key) {
        Node *u = root, *p = NULL;
        while (u) {
            p = u;
            if (u->key == key) {
                splay(u);
                return;
            }
            if (comp(u->key, key)) u = u->r;
            else u = u->l;
        }
        u = new Node(key);
        u->par = p;
        if (!p) root = u;
        else if (comp(p->key, u->key)) p->r = u;
        else p->l = u;
        splay(u);
        sz++;
    }

    Node* find(const T &key) {
        Node *u = root, *p = NULL;
        while (u && u->key != key) {
            p = u;
            if (comp(u->key, key)) u = u->r;
            else u = u->l;
        }
        if (u) {
            splay(u);
            return u;
        }
        if (p) splay(p);
        return NULL;
    }

    Node* join(Node *u, Node *v) {
        if (!u) {
            if (v) v->par = NULL;
            return v;
        }
        Node *mx = subtreeMax(u);
        splay(mx);
        mx->r = v;
        v->par = mx;
        mx->par = NULL;
        return mx;
    }

    pair<Node*, Node*> split(const T &key) {
        Node *u = find(key);
        if (!u) return {NULL, NULL};
        Node *v = u->r;
        if (v)
            v->par = NULL;
        u->r = NULL;
        return {u, v};
    }

    void erase(const T &key) {
        Node *u = find(key);
        if (!u) return;
        splay(u);
        root = join(u->l, u->r);
        delete u;
        sz--;
    }

    void print(Node *u) {
        if (!u) return;
        print(u->l);
        cerr << u->key << ", ";
        print(u->r);
    }

    int size() {
        return sz;
    }
};
