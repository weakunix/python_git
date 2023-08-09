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
    ll val;
    Node *lc, *rc;

    Node(int num) {
        val = num;
        lc = nullptr;
        rc = nullptr;
        return;
    }

    Node(Node *left, Node *right) {
        lc = left;
        rc = right;
        val = 0;
        if (lc) val += lc->val;
        if (rc) val += rc->val;
        return;
    }
};

int n, q;
vector<int> arr;
vector<Node*> rt;

Node* build(int l, int r) {
    if (l == r) return new Node(arr[l]);
    int mid = l + (r - l) / 2;
    return new Node(build(l, mid), build(mid + 1, r));
}

Node* set(Node *node, int l, int r, int arridx, int idx, int num) {
    if (l == r) return new Node(num);
    int mid = l + (r - l) / 2;
    if (idx <= mid) return new Node(set(node->lc, l, mid, arridx, idx, num), node->rc);
    return new Node(node->lc, set(node->rc, mid + 1, r, arridx, idx, num));
}

ll get(Node *node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return node->val;
    int mid = l + (r - l) / 2;
    return get(node->lc, l, mid, a, b) + get(node->rc, mid + 1, r, a, b);
}

int main() {
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    rt.push_back(build(0, n - 1));
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            k--; a--;
            rt[k] = set(rt[k], 0, n - 1, k, a, x);
        }
        else if (t == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            k--; a--; b--;
            cout << get(rt[k], 0, n - 1, a, b) << "\n";
        }
        else {
            int k;
            cin >> k;
            k--;
            rt.push_back(new Node(rt[k]->lc, rt[k]->rc));
        }
    }
	return 0;
}
