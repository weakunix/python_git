#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
ll tar = 0;
vector<ll> hb, ord, par;
vector<threesome> ans1, ans2;
vector<vector<int>> adj;

void dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) {
        if (i != parent) dfs(i, node);
    }
    ord.push_back(node);
    return;
}

int main() {
    cin >> n;
    hb.resize(n);
    par.resize(n);
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> hb[i];
        tar += hb[i];
    }
    assert(tar % n == 0);
    tar /= n;
    for (int i = 0; i < n; i++) hb[i] -= tar;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    for (int i : ord) {
        if (i == 0) assert(hb[i] == 0);
        if (hb[i] == 0) continue;
        if (hb[i] > 0) ans1.push_back({i + 1, {par[i] + 1, hb[i]}});
        else ans2.push_back({par[i] + 1, {i + 1, abs(hb[i])}});
        hb[par[i]] += hb[i];
    }
    cout << ans1.size() + ans2.size() << "\n";
    for (threesome& t : ans1) cout << t.first << " " << t.sec << " " << t.third << "\n";
    for (int i = ans2.size() - 1; i >= 0; i--) cout << ans2[i].first << " " << ans2[i].sec << " " << ans2[i].third << "\n";
	return 0;
}
