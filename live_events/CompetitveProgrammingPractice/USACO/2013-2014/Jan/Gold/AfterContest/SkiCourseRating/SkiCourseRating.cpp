#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 500, M = 500;

int n, m, t, grid[N * M], par[N * M], starting[N * M];
ll ans = 0;
vector<threesome> edges;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    starting[b] += starting[a];
    starting[a] = 0;
    return;
}

int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);

    memset(par, -1, sizeof(par));
    memset(starting, 0, sizeof(starting));

    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> grid[i * m + j];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cur = i * m + j;
            bool b;
            cin >> b;
            if (b) starting[cur]++;

            if (j < m - 1) edges.push_back({abs(grid[cur] - grid[cur + 1]), {cur, cur + 1}});
            if (i < n - 1) edges.push_back({abs(grid[cur] - grid[cur + m]), {cur, cur + m}});
        }
    }

    sort(all(edges));

    if (t == 1) {
        cout << "0\n";
        return 0;
    }

    for (threesome& u : edges) {
        merge(u.sec, u.third);
        int cur = getpar(u.sec);
        if (-par[cur] >= t) {
            ans += (ll) u.first * starting[cur];
            starting[cur] = 0;
        }
    }

    cout << ans << "\n";

	return 0;
}
