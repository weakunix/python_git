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

int n, m, cur;
vector<int> par, stck = {0}, ans;
vector<set<int>> adj;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    if (a == 0) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return;
}

int main() {
    cin >> n >> m;
    par.resize(n, -1);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        merge(a, b);
        adj[a].insert(b);
        adj[b].insert(a);
    }
    for (int i = 0; i < n; i++) {
        if (adj[i].size() % 2 == 1 or (i > 0 and par[i] < -1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    while (not stck.empty()) {
        if (adj[cur].empty()) {
            ans.push_back(cur);
            cur = stck.back();
            stck.pop_back();
            continue;
        }
        int nxt = *adj[cur].begin();
        stck.push_back(cur);
        adj[cur].erase(nxt);
        adj[nxt].erase(cur);
        cur = nxt;
    }
    assert(ans.size() == m + 1);
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] + 1 << " ";
    cout << "\n";
	return 0;
}
