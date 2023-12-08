#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 5000;

int n, m, ht[N], hi[N], par[N], ans = 0;
vector<int> adj[N];
set<int> newadj[N];
multiset<simps> edges;

int dfs1(int node, int parent, int height) {
    ht[node] = height;
    hi[node] = height;

    for (int i : adj[node]) {
        if (i == parent) parent = -1;
        else if (ht[i] != -1) hi[node] = min(ht[i], hi[node]);
        else {
            hi[node] = min(dfs1(i, node, height + 1), hi[node]);
            if (hi[i] > height) edges.erase(edges.find({min(i, node), max(i, node)}));
        }
    }

    return hi[node];
}

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return;
}

int main() {
    memset(ht, -1, sizeof(ht));
    memset(par, -1, sizeof(par));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a > b) swap(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.insert({a, b});
    }

    dfs1(0, -1, 0);

    for (simps s : edges) merge(s.first, s.second);

    for (int i = 0; i < n; i++) for (int j : adj[i]) if (getpar(i) != getpar(j)) newadj[getpar(i)].insert(getpar(j));

    for (int i = 0; i < n; i++) ans += (par[i] < 0 and newadj[i].size() == 1);

    cout << (ans + 1) / 2 << "\n";

	return 0;
}
