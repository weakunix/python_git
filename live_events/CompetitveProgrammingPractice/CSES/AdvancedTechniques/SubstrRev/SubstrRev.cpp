#include <iostream>
#include <cstring>
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

struct Node {
    int sz, pri;
    char val;
    bool rev;
    Node* child[2];

    Node(char vval) {
        sz = 1;
        pri = rand();
        val = vval;
        rev = false;
        child[0] = nullptr;
        child[1] = nullptr;
        return;
    }

    int childsz(int idx) {
        return child[idx] ? child[idx]->sz : 0;
    }

    void prop() {
        if (not rev) return;
        rev = false;
        swap(child[0], child[1]);
        if (child[0]) child[0]->rev = not child[0]->rev;
        if (child[1]) child[1]->rev = not child[1]->rev;
        return;
    }

    void recalc() {
        sz = this->childsz(0) + this->childsz(1) + 1;
        return;
    }
};

int n, m;
Node* rt = nullptr;

pair<Node*, Node*> split(Node* node, int lsz) {
    if (not node) return {nullptr, nullptr};

    node->prop();

    if (node->childsz(0) >= lsz) {
        pair<Node*, Node*> res = split(node->child[0], lsz);
        node->child[0] = res.second;
        node->recalc();
        return {res.first, node};
    }
    pair<Node*, Node*> res = split(node->child[1], lsz - node->childsz(0) - 1);
    node->child[1] = res.first;
    node->recalc();
    return {node, res.second};
}

Node* join(Node* l, Node* r) {
    if (l) l->prop();
    if (r) r->prop();

    if (not l) return r;
    if (not r) return l;

    if (l->pri < r->pri) {
        l->child[1] = join(l->child[1], r);
        l->recalc();
        return l;
    }
    r->child[0] = join(l, r->child[0]);
    r->recalc();
    return r;
}

void dfs(Node* node) {
    if (not node) return;

    node->prop();
    dfs(node->child[0]);
    cout << node->val;
    dfs(node->child[1]);
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        Node* cur = new Node(c);
        rt = join(rt, cur);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        pair<Node*, Node*> res1 = split(rt, a), res2 = split(res1.second, b - a + 1);
        res2.first->rev = true;
        rt = join(join(res1.first, res2.first), res2.second);

        //dfs(rt); cout << "\n";
    }

    dfs(rt);
    cout << "\n";
	return 0;
}
