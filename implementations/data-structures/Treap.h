/**
 * Description: Randomized binary search tree that supports O(log n) split and merge functions.
 * Source: https://cp-algorithms.com/data_structures/treap.html
 * Verification: https://www.spoj.com/problems/ORDERSET/
 * Time: O(log n)
 */

#include "../other/RandomSeed.h"

struct Node {
    int key;
    uint32_t priority;
    Node *l, *r;

    Node(int val) : key(val), priority(rng()), l(NULL), r(NULL) {}
};
using pNode = Node*;

void heapify(pNode t) {
    if (!t)
        return;
    pNode mx = t;
    if (t->l && t->l->priority > mx->priority)
        mx = t->l;
    if (t->r && t->r->priority > mx->priority)
        mx = t->r;
    if (mx != t) {
        swap(t->priority, mx->priority);
        heapify(mx);
    }
}

pNode build(int n, int *a) {
    if (n == 0)
        return NULL;
    int mid = n / 2;
    pNode t = new Node(a[mid]);
    t->l = build(mid, a);
    t->r = build(n - mid - 1, a + mid + 1);
    heapify(t);
    return t;
}

void split(pNode t, int key, pNode &l, pNode &r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split(t->l, key, l, t->l), r = t;
    else
        split(t->r, key, t->r, r), l = t;
}

void merge(pNode &t, pNode l, pNode r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->priority > r->priority)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
}

void insert(pNode &t, pNode it) {
    if (!t)
        t = it;
    else if (it->priority > t->priority)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(it->key < t->key ? t->l : t->r, it);
}

void erase(pNode &t, int key) {
    if (!t)
        return;
    else if (t->key == key)
        merge(t, t->l, t->r);
    else
        erase(key < t->key ? t->l : t->r, key);
}
