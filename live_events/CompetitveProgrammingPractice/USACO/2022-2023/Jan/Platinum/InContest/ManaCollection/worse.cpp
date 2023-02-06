#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, m, q;
vector<ll> mana;
vector<bool> visited;
vector<vector<simps>> revadj;

ll ans(int t, int e) {
    ll best = 0;
    visited[e] = true;
    for (simps& s : revadj[e]) {
        if (not visited[s.first] and s.second <= t) best = max(ans(t - s.second, s.first), best);
    }
    visited[e] = false;
    return best + mana[e] * t;
}

int main() {
    cin >> n >> m;
    mana.resize(n);
    visited.resize(n);
    revadj.resize(n);
    for (int i = 0; i < n; i++) cin >> mana[i];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        revadj[v].push_back({u, w});
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int s, e;
        cin >> s >> e;
        e--;
        cout << ans(s, e) << "\n";
    }
	return 0;
}
