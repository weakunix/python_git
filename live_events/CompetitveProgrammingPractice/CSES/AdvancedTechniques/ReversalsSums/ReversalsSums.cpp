#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

struct tnode {
    int val, pri, sz;
    ll sm;
    bool rev;
    tnode *left, *right;
    
    tnode(int num) {
        val = num, pri = rand(), sz = 1;
        sm = val;
        rev = false;
        left = nullptr, right = nullptr;
        return;
    }
};

int n, m;
tnode *root = nullptr;

int tsz(tnode *treap) {
    return (treap == nullptr) ? 0 : treap->sz;
}

ll tsm(tnode *treap) {
    return (treap == nullptr) ? 0 : treap->sm;
}

void trecalc(tnode *treap) {
    treap->sz = tsz(treap->left) + tsz(treap->right) + 1;
    treap->sm = tsm(treap->left) + tsm(treap->right) + treap->val;
    return;
}

void prop(tnode *treap) {
    if (treap == nullptr or not treap->rev) return;
    treap->rev = false;
    swap(treap->left, treap->right);
    if (treap->left != nullptr) treap->left->rev ^= 1;
    if (treap->right != nullptr) treap->right->rev ^= 1;
    return;
}

void split(tnode *treap, tnode *&left, tnode *&right, int val) {
    prop(treap);
    if (treap == nullptr) {
        left = nullptr, right = nullptr;
        return;
    }
    if (tsz(treap->left) < val) {
        split(treap->right, treap->right, right, val - tsz(treap->left) - 1);
        left = treap;
    }
    else {
        split(treap->left, left, treap->left, val);
        right = treap;
    }
    trecalc(treap);
    return;
}

void merge(tnode *&treap, tnode *left, tnode *right) {
    prop(left), prop(right);
    if (left == nullptr) {
        treap = right;
        return;
    }
    if (right == nullptr) {
        treap = left;
        return;
    }
    if (left->pri < right->pri) {
        merge(left->right, left->right, right);
        treap = left;
    }
    else {
        merge(right->left, left, right->left);
        treap = right;
    }
    trecalc(treap);
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        merge(root, root, new tnode(cur));
    }
    for (int i = 0; i < m; i++) {
        int t, l, r;
        tnode *a, *b, *c;
        cin >> t >> l >> r;
        l--; r--;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        assert(b != nullptr);
        if (t == 1) b->rev ^= 1;
        else cout << b->sm << "\n";
        merge(root, a, b);
        merge(root, root, c);
    }
	return 0;
}
