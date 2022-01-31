// Source: https://codeforces.com/blog/entry/83969
// Example of submission that solves sort subarray queries: https://atcoder.jp/contests/abc237/submissions/28967721

template<typename T, bool MULTI=false, typename SIZE_T=int> struct sms {
	struct node {
		node *l, *r; // left and right childs
		SIZE_T cnt; // subtree leaf count
		node() : l(NULL), r(NULL), cnt(0) {}
		void update() { // update subtree leaf count
			cnt = 0;
			if (l) cnt += l->cnt;
			if (r) cnt += r->cnt;
		}
	};

	node* root;
	T N;

	sms() : root(NULL), N(0) {}
	sms(T v) : sms() { while (v >= N) N = 2*N+1; }
	sms(const sms& t) : root(NULL), N(t.N) { // copy - O(t log(N))
		for (SIZE_T i = 0; i < t.size(); i++) {
			T at = t[i];
			SIZE_T qt = t.count(at);
			insert(at, qt);
			i += qt-1;
		}
	}
	sms(initializer_list<T> v) : sms() { for (T i : v) insert(i); }
	~sms() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	friend void swap(sms& a, sms& b) { // O(1) swap
		swap(a.root, b.root), swap(a.N, b.N);
	}
	SIZE_T size() const { return root ? root->cnt : 0; }
	SIZE_T count(node* x) const { return x ? x->cnt : 0; }
	void clear() {
		sms tmp;
		swap(*this, tmp);
	}
	void expand(T v) { // increase N so value 'v' will fit
		for (; N < v; N = 2*N+1) if (root) {
			node* nroot = new node();
			nroot->l = root;
			root = nroot;
			root->update();
		}
	}

	node* insert(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) at = new node();
		if (l == r) {
			at->cnt += qt;
			if (!MULTI) at->cnt = 1;
			return at;
		}
		T m = l + (r-l)/2;
		if (idx <= m) at->l = insert(at->l, idx, qt, l, m);
		else at->r = insert(at->r, idx, qt, m+1, r);
		return at->update(), at;
	}
	void insert(T v, SIZE_T qt=1) { // insert 'qt' occurrences of 'v'
		if (qt <= 0) return erase(v, -qt);
		assert(v >= 0);
		expand(v);
		root = insert(root, v, qt, 0, N);
	}

	node* erase(node* at, T idx, SIZE_T qt, T l, T r) {
		if (!at) return at;
		if (l == r) at->cnt = at->cnt < qt ? 0 : at->cnt - qt;
		else {
			T m = l + (r-l)/2;
			if (idx <= m) at->l = erase(at->l, idx, qt, l, m);
			else at->r = erase(at->r, idx, qt, m+1, r);
			at->update();
		}
		if (!at->cnt) delete at, at = NULL; // 'cnt' is always positive
		return at;
	}
	void erase(T v, SIZE_T qt=1) { // erase 'qt' occurrences of 'v'
		if (v < 0 or v > N or !qt) return;
		if (qt < 0) insert(v, -qt);
		root = erase(root, v, qt, 0, N);
	}
	void erase_all(T v) { // remove all occurrences of 'v'
		if (v < 0 or v > N) return;
		root = erase(root, v, numeric_limits<SIZE_T>::max(), 0, N);
	}

	SIZE_T count(node* at, T a, T b, T l, T r) const {
		if (!at or b < l or r < a) return 0;
		if (a <= l and r <= b) return at->cnt;
		T m = l + (r-l)/2;
		return count(at->l, a, b, l, m) + count(at->r, a, b, m+1, r);
	}
	SIZE_T count(T v) const { return count(root, v, v, 0, N); }
	SIZE_T order_of_key(T v) { return count(root, 0, v-1, 0, N); }
	SIZE_T lower_bound(T v) { return order_of_key(v); }

	const T operator [](SIZE_T i) const { // i-th smallest element (0 -> smallest)
		assert(i >= 0 and i < size());
		node* at = root;
		T l = 0, r = N;
		while (l < r) {
			T m = l + (r-l)/2;
			if (count(at->l) > i) at = at->l, r = m;
			else {
				i -= count(at->l);
				at = at->r; l = m+1;
			}
		}
		return l;
	}

	node* merge(node* l, node* r) {
		if (!l or !r) return l ? l : r;
		if (!l->l and !l->r) { // 'l' is a leaf
			if (MULTI) l->cnt += r->cnt;
			delete r;
			return l;
		}
		l->l = merge(l->l, r->l), l->r = merge(l->r, r->r);
		l->update(), delete r;
		return l;
	}
	void merge(sms& s) { // merge two sets
		if (N > s.N) swap(*this, s);
		expand(s.N);
		root = merge(root, s.root);
		s.root = NULL;
	}

	node* split(node*& x, SIZE_T k) {
		if (k <= 0 or !x) return NULL;
		node* ret = new node();
		if (!x->l and !x->r) x->cnt -= k, ret->cnt += k;
		else {
			if (k <= count(x->l)) ret->l = split(x->l, k);
			else {
				ret->r = split(x->r, k - count(x->l));
				swap(x->l, ret->l);
			}
			ret->update(), x->update();
		}
		if (!x->cnt) delete x, x = NULL; // 'cnt' is always positive
		return ret;
	}
	void split(SIZE_T k, sms& s) { // get the 'k' smallest elements
		s.clear();
		s.root = split(root, min(k, size()));
		s.N = N;
	}
	// get all elements smaller than 'k'
	void split_val(T k, sms& s) { split(order_of_key(k), s); }
};

/*
How to use:

This code can represent either set of multiset. To create an empty structure:

sms<int> s; // set
sms<int, true> s; // multiset
sms<int, true, long long> s; // multiset, if you want to insert more than 1e9 elements

Most of the operations look similar to std::set:

sms<int, true> s; // multiset
s.insert(3); // insert value '3'
s.insert(4, 3); // insert value '4' three times
s.erase(4); // erase one occurrence of value '4'
s.erase(3, 5); // erase 5 occurrences of value '3'
s.erase_all(4); // erase all occurrences of value '4'

Order statistic operations work as well:

sms<int, true> s = {4, 7, 3, 4, 1, 6, 3}; // now s = {1, 3, 3, 4, 4, 6, 7}
cout << s.order_of_key(4) << endl; // prints "3"
cout << s[0] << " " << s[3] << " " << s[5] << endl; // prints "1 4 6"

Finally, split and merge operations look like this:

sms<int, true> s = {1, 3, 3, 4, 4, 6, 7};
sms<int, true> s2;
s.split(4, s2); // get the 4 smallest elements from s
// now s = {4, 6, 7} and s2 = {1, 3, 3, 4}

sms<int, true> s3 = {2, 4, 6};
s3.merge(s2);
// now s3 = {1, 2, 3, 3, 4, 4, 6}
*/
