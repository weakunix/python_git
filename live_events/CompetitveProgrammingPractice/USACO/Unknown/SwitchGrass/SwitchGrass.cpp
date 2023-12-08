#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 2e5;

int n, m, k, q, col[N], par[N], parlen[N];
bool vis[N];
vector<simps> adj[N];
priority_queue<threesome> pq;
multiset<int> ans, bestcol[N];
map<int, multiset<int>> child[N];

int main() {
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);

    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    memset(par, -1, sizeof(par));
    memset(vis, false, sizeof(vis));
    vis[0] = true;

    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    for (int i = 0; i < n; i++) {
        cin >> col[i];
        col[i]--;
    }

    for (simps& s : adj[0]) pq.push({-s.second, {0, s.first}});
    while (pq.size()) {
        int from = pq.top().sec, to = pq.top().third, len = -pq.top().first;
        pq.pop();
        if (vis[to]) continue;
        
        vis[to] = true;
        par[to] = from;
        parlen[to] = len;
        child[from][col[to]].insert(len);

        for (simps& s : adj[to]) pq.push({-s.second, {to, s.first}});
    }

    for (int i = 0; i < n; i++) {
        for (auto& u : child[i]) {
            if (u.first == col[i]) continue;
            bestcol[i].insert(*u.second.begin());
        }
        if (bestcol[i].size()) ans.insert(*bestcol[i].begin());
    }

    for (int i = 0; i < q; i++) {
        int node, nw;
        cin >> node >> nw;
        node--; nw--;

        if (col[node] == nw) {
            cout << *ans.begin() << "\n";
            continue;
        }

        if (par[node] != -1) {
            if (bestcol[par[node]].size()) ans.erase(ans.find(*bestcol[par[node]].begin())); //ans rem
            if (col[node] != col[par[node]]) bestcol[par[node]].erase(bestcol[par[node]].find(*child[par[node]][col[node]].begin())); //bestcol rem
            if (nw != col[par[node]] and child[par[node]].count(nw)) bestcol[par[node]].erase(bestcol[par[node]].find(*child[par[node]][nw].begin()));
            child[par[node]][col[node]].erase(child[par[node]][col[node]].find(parlen[node])); //child rem
            if (child[par[node]][col[node]].empty()) child[par[node]].erase(col[node]);

            child[par[node]][nw].insert(parlen[node]); //child add
            if (col[node] != col[par[node]] and child[par[node]].count(col[node])) bestcol[par[node]].insert(*child[par[node]][col[node]].begin()); //bestcol add
            if (nw != col[par[node]]) bestcol[par[node]].insert(*child[par[node]][nw].begin());
            if (bestcol[par[node]].size()) ans.insert(*bestcol[par[node]].begin()); //ans add
        }

        if (child[node].size()) {
            if (bestcol[node].size()) ans.erase(ans.find(*bestcol[node].begin())); //ans rem
            if (child[node].count(nw)) bestcol[node].erase(bestcol[node].find(*child[node][nw].begin())); //bestcol rem

            if (child[node].count(col[node])) bestcol[node].insert(*child[node][col[node]].begin()); //bestcol add
            if (bestcol[node].size()) ans.insert(*bestcol[node].begin()); //ans add
        }

        col[node] = nw;
        cout << *ans.begin() << "\n";
    }

	return 0;
}
