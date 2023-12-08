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

const int N = 1e5 + 1, L = 18;

int n, q, ht[N], st[L][2 * N], sz = 0, idx[N], lg[2 * N];
vector<int> adj[N];

void dfs(int node, int parent, int height) {
    st[0][sz] = node;
    idx[node] = sz;
    sz++;
    ht[node] = height;

    for (int i : adj[node]) {
        if (i != parent) {
            dfs(i, node, height + 1);
            st[0][sz] = node;
            sz++;
        }
    }

    return;
}

int getlca(int a, int b) {
    a = idx[a]; b = idx[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    if (ht[st[len][a]] < ht[st[len][b - (1 << len) + 1]]) return st[len][a];
    return st[len][b - (1 << len) + 1];
}

int main() {
    lg[1] = 0;
    for (int i = 2; i < 2 * N; i++) lg[i] = lg[i / 2] + 1;

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0);

    for (int i = 1; (1 << i) <= sz; i++) {
        for (int j = 0; j + (1 << i) <= sz; j++) {
            if (ht[st[i - 1][j]] < ht[st[i - 1][j + (1 << (i - 1))]]) st[i][j] = st[i - 1][j];
            else st[i][j] = st[i - 1][j + (1 << (i - 1))];
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b, l;
        cin >> a >> b;
        a--; b--;
        l = getlca(a, b);
        cout << ht[a] + ht[b] - 2 * ht[l] << "\n";
    }

	return 0;
}
