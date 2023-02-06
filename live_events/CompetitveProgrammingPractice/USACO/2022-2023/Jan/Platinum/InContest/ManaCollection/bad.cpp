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
vector<vector<simps>> revadj;

ll ans(int t, int e, int visited) {
    ll best = 0;
    visited ^= (1 << e);
    for (simps& s : revadj[e]) {
        if ((visited & (1 << s.first)) == 0 and s.second < t) best = max(ans(t - s.second, s.first, visited), best);
    }
    return best + mana[e] * t;
}

int main() {
    cin >> n >> m;
    mana.resize(n);
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
        cout << ans(s, e, 0) << "\n";
    }
	return 0;
}
