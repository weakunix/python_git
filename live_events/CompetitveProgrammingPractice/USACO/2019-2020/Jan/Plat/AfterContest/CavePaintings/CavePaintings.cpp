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

const int N = 1000, M = 1000, K = 1e6, modval = 1e9 + 7;

int n, m, cnt = 0, grid[N][M], par[K];
ll ans = 1;
set<int> rts;
map<int, vector<int>> adj;

int getpar(int node) {
    if (par[node] < 0)  return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return;
}

ll calc(int node) {
    ll res = 1;
    for (int i : adj[node]) res = res * calc(i) % modval;
    return res + 1;
}

int main() {
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);

    memset(par, -1, sizeof(par));

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.') {
                if (j > 0 and grid[i][j - 1] != -1) grid[i][j] = grid[i][j - 1];
                else {
                    grid[i][j] = cnt;
                    cnt++;
                }
            }
            else grid[i][j] = -1;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        map<int, int> mp;
        for (int j = 0; j < m; j++) {
            if (grid[i + 1][j] != -1 and grid[i][j] != -1) {
                rts.erase(grid[i + 1][j]);
                if (mp.count(grid[i + 1][j])) merge(mp[grid[i + 1][j]], grid[i][j]);
                else mp[grid[i + 1][j]] = grid[i][j];
            }
        }

        for (int j = 0; j < m; j++) {
            if (grid[i][j] != -1) {
                grid[i][j] = getpar(grid[i][j]);
                rts.insert(grid[i][j]);
            }
        }

        for (auto u : mp) adj[getpar(u.second)].push_back(u.first);
    }

    for (int i : rts) ans = ans * calc(i) % modval;

    cout << ans << "\n";

	return 0;
}
