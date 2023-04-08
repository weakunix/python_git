#include <iostream>
#include <string>
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
    int pri, sz;
    char val;
    tnode *child[2], *par;

    tnode(char c) {
        val = c;
        pri = rand();
        sz = 1;
        child[0] = nullptr;
        child[1] = nullptr;
        par = nullptr;
        return;
    }
};

int n, m;
string s;
tnode *root;

int treapsize(tnode *treap) {
    return (treap == nullptr) ? 0 : treap->sz;
}

void split(tnode *treap, tnode *&left, tnode *&right, int idx) {
    if (treap == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }
    if (treapsize(treap->child[0]) < idx) {
        split(treap->child[1], treap->child[1], right, idx - treapsize(treap->child[0]) - 1);
        left = treap;
    }
    else {
        split(treap->child[0], left, treap->child[0], idx);
        right = treap;
    }
    treap->sz = treapsize(treap->child[0]) + treapsize(treap->child[1]) + 1;
    return;
}

void merge(tnode *&treap, tnode *left, tnode *right) {
    if (left == nullptr) {
        treap = right;
        return;
    }
    if (right == nullptr) {
        treap = left;
        return;
    }
    if (left->pri < right->pri) {
        merge(left->child[1], left->child[1], right);
        treap = left;
    }
    else {
        merge(right->child[0], left, right->child[0]);
        treap = right;
    }
    treap->sz = treapsize(treap->child[0]) + treapsize(treap->child[1]) + 1;
    return;
}

void getans(tnode *treap) {
    if (treap == nullptr) return;
    getans(treap->child[0]);
    cout << treap->val;
    getans(treap->child[1]);
    return;
}

int main() {
    cin >> n >> m >> s;
    for (char c : s) merge(root, root, new tnode(c));
    for (int i = 0; i < m; i++) {
        int l, r;
        tnode *a, *b, *c, *d;
        cin >> l >> r;
        l--; r--;
        split(root, a, b, l);
        split(b, c, d, r - l + 1);
        merge(root, a, d);
        merge(root, root, c);
    }
    getans(root);
    cout << "\n";
	return 0;
}
