/**
 * Description: Performs range queries and range updates. Supports sparse indices.
 * Source: https://ideone.com/0QK4CX
 * Verification: https://acm.timus.ru/problem.aspx?space=1&num=1439
 * Time: O(log n) query and update
 */

struct Node {
    int ans, l, r;
    Node *left, *right;

    Node(int _l, int _r) : ans(0), l(_l), r(_r), left(NULL), right(NULL) {}

    void extend() {
        if (!left) {
            int m = (l + r) / 2;
            left = new Node(l, m);
            right = new Node(m+1, r);
        }
    }

    int query(int i, int j) {
        if (i > r || j < l)
            return 0;
        if (i <= l && r <= j)
            return ans;

        extend();
        return left->query(i, j) + right->query(i, j);
    }

    void update(int idx, int val) {
        if (l == r) {
            ans = val;
            return;
        }

        extend();
        int m = (l + r) / 2;
        if (idx <= m)
            left->update(idx, val);
        else
            right->update(idx, val);
        ans = left->ans + right->ans;
    }
};
