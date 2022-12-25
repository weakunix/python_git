#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

int n, m;
ll ans = 0;
vector<int> ord, par, deg;
vector<bool> activated;
vector<vector<int>> adj;
vector<map<int, int>> concomps;

int getparent(int node) {
    if (par[node] < 0) return node;
    par[node] = getparent(par[node]);
    return par[node];
}

void connect(int a, int b) {
    int p = getparent(a);
    concomps[p][deg[a]]--;
    if (concomps[p][deg[a]] == 0) concomps[p].erase(deg[a]);
    concomps[p][deg[b]]--;
    if (concomps[p][deg[b]] == 0) concomps[p].erase(deg[b]);
    deg[a]++;
    deg[b]++;
    concomps[p][deg[a]]++;
    concomps[p][deg[b]]++;
    ans = max((ll) -par[p] * concomps[p].begin()->first, ans);
    return;
}

void merge(int a, int b) {
    int x = getparent(a), y = getparent(b);
    if (x != y) {
        if (par[x] > par[y]) swap(x, y);
        par[y] += par[x];
        par[x] = y;
        for (auto u : concomps[x]) concomps[y][u.first] += u.second;
    }
    connect(a, b);
    return;
}

void genord() {
    vector<int> curdeg(n);
    vector<bool> visited(n);
    set<simps> sorteddeg;
    for (int i = 0; i < n; i++) {
        curdeg[i] = adj[i].size();
        sorteddeg.insert({curdeg[i], i});
    }
    while (not sorteddeg.empty()) {
        int node = sorteddeg.begin()->second;
        visited[node] = true;
        ord.push_back(node);
        sorteddeg.erase({curdeg[node], node});
        for (int i : adj[node]) {
            if (visited[i]) continue;
            sorteddeg.erase({curdeg[i], i});
            curdeg[i]--;
            sorteddeg.insert({curdeg[i], i});
        }
    }
    return;
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    par.resize(n, -1);
    deg.resize(n);
    activated.resize(n);
    concomps.resize(n);
    for (int i = 0; i < n; i++) concomps[i][0] = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    genord();
    for (int i = n - 1; i >= 0; i--) {
        int node = ord[i];
        activated[node] = true;
        for (int j : adj[node]) {
            if (activated[j]) merge(node, j);
        }
    }
    cout << ans << "\n";
	return 0;
}
