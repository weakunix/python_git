#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int n, q;
vector<int> e, depthordidx, bit, ord, st, en;
vector<simps> depthord;
vector<vector<int>> adj;
vector<vector<simps>> sparse;

int lg(int n) {
    return log(n) / log(2) + 1;
}

void dfs(int node, int parent, int depth, int val) {
    val ^= e[node];
    ord.push_back(node);
    st[node] = ord.size();
    depthordidx[node] = depthord.size();
    depthord.push_back({depth, node});
    for (int i : adj[node]) {
        if (i != parent) {
            dfs(i, node, depth + 1, val);
            depthord.push_back({depth, node});
        }
    }
    ord.push_back(node);
    en[node] = ord.size();
    return;
}

void generatesparse() {
    int pow = 0;
    sparse.push_back({});
    for (simps s : depthord) sparse[0].push_back(s);
    for (int i = 2; i < 2 * n; i *= 2) {
        pow++;
        sparse.push_back({});
        for (int j = 0; j < 2 * n - i; j++) sparse[pow].push_back(min(sparse[pow - 1][j], sparse[pow - 1][j + i / 2]));
    }
    return;
}

int lca(int a, int b) {
    a = depthordidx[a];
    b = depthordidx[b];
    if (a > b) swap(a, b);
    int len = lg(b - a + 1) - 1;
    return min(sparse[len][a], sparse[len][b - (1 << len) + 1]).second;
}

void setidx(int idx, int val) {
    while (idx <= 2 * n) {
        bit[idx] ^= val;
        idx += idx & (-idx);
    }
    return;
}

int getpfx(int idx) {
    int res = 0;
    while (idx > 0) {
        res ^= bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

    cin >> n >> q;
    e.resize(n);
    adj.resize(n);
    depthordidx.resize(n);
    bit.resize(2 * n + 1);
    st.resize(n);
    en.resize(n);
    for (int i = 0; i < n; i++) cin >> e[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0, 0);
    assert(depthord.size() == 2 * n - 1);
    generatesparse();

    for (int i = 0; i < n; i++) {
        setidx(st[i], e[i]);
        setidx(en[i], e[i]);
    }
    
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx, val;
            cin >> idx >> val;
            idx--;
            setidx(st[idx], e[idx] ^ val);
            setidx(en[idx], e[idx] ^ val);
            e[idx] = val;
        }
        else {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            cout << (getpfx(st[a]) ^ getpfx(st[b]) ^ e[lca(a, b)]) << "\n";
        }
    }

	return 0;
}
