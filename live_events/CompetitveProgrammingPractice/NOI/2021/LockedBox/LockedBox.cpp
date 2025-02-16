#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int modval = 998244353;

struct Mat {
    ll val[2][2];

    Mat() {
        val[0][0] = 1;
        val[0][1] = 0;
        val[1][0] = 0;
        val[1][1] = 1;
        return;
    }

    Mat(ll a, ll b, ll c, ll d) {
        val[0][0] = a;
        val[0][1] = b;
        val[1][0] = c;
        val[1][1] = d;
        return;
    }

    ~Mat() {}
};


Mat operator*(Mat a, Mat b) {
    Mat res(0, 0, 0, 0);
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++) res.val[i][j] = (res.val[i][j] + a.val[i][k] * b.val[k][j] % modval) % modval;
    return res;
}

struct Treap {
    int pri, sz;
    Mat val, prod;
    Treap* l;
    Treap* r;

    Treap() : pri(rng()), sz(1), val(Mat()), prod(Mat()), l(nullptr), r(nullptr) {}

    Treap(Mat _val) : pri(rng()), sz(1), val(_val), prod(_val), l(nullptr), r(nullptr) {}

    ~Treap() {}
};

int getsz(Treap* node) {
    return (node ? node->sz : 0);
}

Mat getprod(Treap* node) {
    return (node ? node->prod : Mat());
}

void upd(Treap* node) {
    node->sz = getsz(node->l) + 1 + getsz(node->r);
    node->prod = getprod(node->l) * node->val * getprod(node->r);
    return;
}

void merge(Treap* &node, Treap* l, Treap* r) {
    if (not l) {
        node = r;
        return;
    }
    if (not r) {
        node = l;
        return;
    }

    if (l->pri < r->pri) {
        merge(l->r, l->r, r);
        node = l;
    }
    else {
        merge(r->l, l, r->l);
        node = r;
    }

    upd(node);

    return;
}

void split(Treap* node, Treap* &l, Treap* &r, int k) {
    if (not node) {
        l = nullptr;
        r = nullptr;
        return;
    }

    if (k <= getsz(node->l)) {
        split(node->l, l, node->l, k);
        r = node;
    }
    else {
        split(node->r, node->r, r, k - getsz(node->l) - 1);
        l = node;
    }

    upd(node);

    return;
}

int n, q;
Mat w(1, 0, 1, 1), e(2, 1, modval - 1, 0);
Treap *rt = new Treap(w), *frt = new Treap(w), *rrt = new Treap(w), *frrt = new Treap(w);

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'W') {
            merge(rt, rt, new Treap(w));
            merge(frt, frt, new Treap(e));
            merge(rrt, new Treap(w), rrt);
            merge(frrt, new Treap(e), frrt);
        }
        else {
            merge(rt, rt, new Treap(e));
            merge(frt, frt, new Treap(w));
            merge(rrt, new Treap(e), rrt);
            merge(frrt, new Treap(w), frrt);
        }
    }

    cout << rt->prod.val[0][0] << " " << rt->prod.val[1][0] << "\n";

    n++;

    for (int i = 0; i < q; i++) {
        char op;
        string s;
        cin >> s;
        op = s[0];
        if (op == 'A') {
            char c;
            cin >> c;
            if (c == 'W') {
                merge(rt, rt, new Treap(w));
                merge(frt, frt, new Treap(e));
                merge(rrt, new Treap(w), rrt);
                merge(frrt, new Treap(e), frrt);
            }
            else {
                merge(rt, rt, new Treap(e));
                merge(frt, frt, new Treap(w));
                merge(rrt, new Treap(e), rrt);
                merge(frrt, new Treap(w), frrt);
            }
            n++;
        }
        else if (op == 'F') {
            int l, r;
            Treap *a, *b, *c, *d;
            cin >> l >> r;
            
            split(rt, rt, b, r + 1);
            split(rt, rt, a, l);
            split(frt, frt, d, r + 1);
            split(frt, frt, c, l);
            merge(rt, rt, c);
            merge(rt, rt, b);
            merge(frt, frt, a);
            merge(frt, frt, d);

            split(rrt, rrt, b, n - l);
            split(rrt, rrt, a, n - r - 1);
            split(frrt, frrt, d, n - l);
            split(frrt, frrt, c, n - r - 1);
            merge(rrt, rrt, c);
            merge(rrt, rrt, b);
            merge(frrt, frrt, a);
            merge(frrt, frrt, d);
        }
        else {
            int l, r;
            Treap *a, *b, *c, *d;
            cin >> l >> r;

            split(rt, rt, b, r + 1);
            split(rt, rt, a, l);
            split(rrt, rrt, d, n - l);
            split(rrt, rrt, c, n - r - 1);
            merge(rt, rt, c);
            merge(rt, rt, b);
            merge(rrt, rrt, a);
            merge(rrt, rrt, d);

            split(frt, frt, b, r + 1);
            split(frt, frt, a, l);
            split(frrt, frrt, d, n - l);
            split(frrt, frrt, c, n - r - 1);
            merge(frt, frt, c);
            merge(frt, frt, b);
            merge(frrt, frrt, a);
            merge(frrt, frrt, d);
        }
        cout << rt->prod.val[0][0] << " " << rt->prod.val[1][0] << "\n";
    }

	return 0;
}
