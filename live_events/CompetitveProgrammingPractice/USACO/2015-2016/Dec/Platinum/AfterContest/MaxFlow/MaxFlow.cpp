#include <iostream>
#include <cstdio>
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

const int N = 5e4 + 1, L = 17;

int n, k, st[L][2 * N], par[N], ht[N], sz = 0, idx[N], lg[2 * N], pfx[N], ans = 0;
vector<int> adj[N];

void dfs1(int node, int parent, int height) {
    st[0][sz] = node;
    idx[node] = sz;
    sz++;
    par[node] = parent;
    ht[node] = height;
    
    for (int i : adj[node]) {
        if (i != parent) {
            dfs1(i, node, height + 1);
            st[0][sz] = node;
            sz++;
        }
    }

    return;
}

int dfs2(int node) {
    for (int i : adj[node]) if (i != par[node]) pfx[node] += dfs2(i);
    ans = max(pfx[node], ans);
    return pfx[node];
}

int getlca(int a, int b) {
    a = idx[a]; b = idx[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    if (ht[st[len][a]] < ht[st[len][b - (1 << len) + 1]]) return st[len][a];
    return st[len][b - (1 << len) + 1];
}

int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    memset(pfx, 0, sizeof(pfx));
    lg[1] = 0;
    for (int i = 2; i < 2 * N; i++) lg[i] = lg[i / 2] + 1;

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(0, -1, 0);

    for (int i = 1; (1 << i) <= sz; i++) {
        for (int j = 0; j + (1 << i) <= sz; j++) {
            if (ht[st[i - 1][j]] < ht[st[i - 1][j + (1 << (i - 1))]]) st[i][j] = st[i - 1][j];
            else st[i][j] = st[i - 1][j + (1 << (i - 1))];
        }
    }

    for (int i = 0; i < k; i++) {
        int a, b, l;
        cin >> a >> b;
        a--; b--;
        if (ht[a] > ht[b]) swap(a, b);
        l = getlca(a, b);

        if (l == a) {
            pfx[b]++;
            if (l != 0) pfx[par[l]]--;
            continue;
        }
        pfx[a]++;
        pfx[b]++;
        pfx[l]--;
        if (l != 0) pfx[par[l]]--;
    }

    dfs2(0);
    cout << ans << "\n";

	return 0;
}
