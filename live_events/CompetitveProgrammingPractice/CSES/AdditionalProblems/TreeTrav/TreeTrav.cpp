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

const int N = 1e5;

struct Node {
    int val;
    Node *c1, *c2;

    Node(int v) {
        val = v;
        c1 = nullptr;
        c2 = nullptr;
        return;
    }
};

int n, arr[N], idx[N];

Node* dfs1(int l, int r, int lidx, int ridx) {
    if (r < l) return nullptr;

    Node* cur = new Node(arr[l]);

    int mididx = idx[arr[l]], lsz = mididx - lidx;
    cur->c1 = dfs1(l + 1, l + lsz, lidx, mididx - 1);
    cur->c2 = dfs1(l + lsz + 1, r, mididx + 1, ridx);

    return cur;
}

void dfs2(Node* node) {
    if (not node) return;
    dfs2(node->c1);
    dfs2(node->c2);
    cout << node->val + 1 << " ";
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        idx[cur - 1] = i;
    }

    Node* rt = dfs1(0, n - 1, 0, n - 1);
    dfs2(rt);
    cout << "\n";

	return 0;
}
