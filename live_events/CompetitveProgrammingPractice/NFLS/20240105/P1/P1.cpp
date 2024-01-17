#include <iostream>
#include <cstdio>
#include <cstring>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5, M = 3e5;

int n, m, c, q, dsu[N], par[N], w[N], col[N];
vector<simps> adj[N];
threesome edges[M];
multiset<int> ans, child[N];
map<int, multiset<int>> chcol[N];

int getpar(int node) {
    if (dsu[node] < 0) return node;
    dsu[node] = getpar(dsu[node]);
    return dsu[node];
}

bool merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return false;
    if (dsu[a] < dsu[b]) swap(a, b);
    dsu[b] += dsu[a];
    dsu[a] = b;
    return true;
}

void dfs(int node, int parent, int weight) {
    par[node] = parent;
    w[node] = weight;
    for (simps& s : adj[node]) {
        if (s.first == parent) continue;
        dfs(s.first, node, s.second);
        chcol[node][col[s.first]].insert(s.second);
    }
    for (auto& u : chcol[node]) if (u.first != col[node]) child[node].insert(*u.second.begin());
    if (child[node].size()) ans.insert(*child[node].begin());
    return;
}

int main() {
    //freopen("noip.in", "r", stdin);
    //freopen("noip.out", "w", stdout);
    
    memset(dsu, -1, sizeof dsu);

    cin >> n >> m >> c >> q;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].sec >> edges[i].third >> edges[i].first;
        edges[i].sec--; edges[i].third--;
    }
    for (int i = 0; i < n; i++) {
        cin >> col[i];
        col[i]--;
    }

    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        int a = edges[i].sec, b = edges[i].third, c = edges[i].first;
        if (merge(a, b)) {
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
        }
    }
    dfs(0, -1, -1);

    for (int i = 0; i < q; i++) {
        int node, nw, p;
        cin >> node >> nw;
        node--; nw--;
        p = par[node];

        if (nw != col[node]) {
            if (chcol[node].size()) {
                if (child[node].size()) ans.erase(ans.find(*child[node].begin()));
                if (chcol[node].count(nw)) child[node].erase(child[node].find(*chcol[node][nw].begin()));
                if (chcol[node].count(col[node])) child[node].insert(*chcol[node][col[node]].begin());
                if (child[node].size()) ans.insert(*child[node].begin());
            }

            if (p != -1) {
                if (child[p].size()) ans.erase(ans.find(*child[p].begin()));
                if (col[node] != col[p] and chcol[p].count(col[node])) child[p].erase(child[p].find(*chcol[p][col[node]].begin()));
                if (nw != col[p] and chcol[p].count(nw)) child[p].erase(child[p].find(*chcol[p][nw].begin()));
                chcol[p][col[node]].erase(chcol[p][col[node]].find(w[node]));
                chcol[p][nw].insert(w[node]);
                if (chcol[p][col[node]].empty()) chcol[p].erase(col[node]);
                else if (col[node] != col[p]) child[p].insert(*chcol[p][col[node]].begin());
                if (nw != col[p]) child[p].insert(*chcol[p][nw].begin());
                if (child[p].size()) ans.insert(*child[p].begin());
            }
        }

        col[node] = nw;
        cout << *ans.begin() << "\n";
    }

	return 0;
}
