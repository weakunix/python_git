#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, q;
vector<int> st, en, preord;
vector<ll> selfcolor, childcolor;
vector<vector<int>> adj;
vector<set<int>> colors;

void setidx(vector<ll>& bit, int idx, int change) {
    while (idx <= n) {
        bit[idx] += change;
        idx += idx & (-idx);
    }
    return;
}

ll getpfx(vector<ll>& bit, int idx) {
    ll res = 0;
    while (idx > 0) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void dfs(int node, int parent) {
    preord.push_back(node);
    st[node] = preord.size() - 1;
    for (int i : adj[node]) {
        if (i != parent) dfs(i, node);
    }
    en[node] = preord.size() - 1;
    return;
}

int main() {
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);

    cin >> n >> q;
    st.resize(n);
    en.resize(n);
    selfcolor.resize(n + 1);
    childcolor.resize(n + 1);
    adj.resize(n);
    colors.resize(1e5);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, c;
            cin >> x >> c;
            x--;
            c--;
            auto it = colors[c].upper_bound(st[x]);
            if (it != colors[c].begin()) {
                it--;
                if (en[preord[*it]] >= st[x]) continue;
            }
            colors[c].insert(st[x]);
            setidx(selfcolor, st[x] + 1, 1);
            setidx(selfcolor, en[x] + 2, -1);
            setidx(childcolor, st[x] + 1, en[x] - st[x] + 1);
            it = colors[c].upper_bound(st[x]);
            while (it != colors[c].end() and *it <= en[x]) {
                setidx(selfcolor, *it + 1, -1);
                setidx(selfcolor, en[preord[*it]] + 2, 1);
                setidx(childcolor, *it + 1, -(en[preord[*it]] - *it + 1));
                colors[c].erase(*it);
                it = colors[c].upper_bound(st[x]);
            }
        }
        else {
            int x;
            cin >> x;
            x--;
            cout << getpfx(selfcolor, st[x] + 1) * (en[x] - st[x] + 1) + getpfx(childcolor, en[x] + 1) - getpfx(childcolor, st[x] + 1) << "\n";
        }
    }

	return 0;
}
