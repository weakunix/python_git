#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 100, K = 100, modval = 998244353;

int t, n, k, m[K], ans;
ll prv[N][2 * N], nxt[N][2 * N];
vector<int> adj[K][2 * N];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

void subcase() {
    ans = 1;
    for (int i = 0; i < k; i++) for (int j = 0; j < 2 * N; j++) adj[i][j].clear();

    cin >> k;
    for (int i = 0; i < k; i++) cin >> n;
    for (int i = 0; i < k - 1; i++) cin >> m[i];
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < m[i]; j++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[i][u].pb(v);
        }
    }

    clr(nxt, 0);
    for (int i = 0; i < n; i++) nxt[i][i] = 1;

    for (int i = 0; i < k - 1; i++) {
        memcpy(prv, nxt, sizeof(nxt));
        clr(nxt, 0);
        for (int j = 0; j < n; j++) for (int l = 0; l < 2 * n; l++) for (int o : adj[i][l]) nxt[j][o] = (nxt[j][o] + prv[j][l]) % modval;
    }

    for (int i = 0; i < n; i++) {
        if (nxt[i][i] == 0) {
            bool works = false;
            for (int j = i + 1; j < n; j++) {
                if (nxt[j][i] == 0) continue;
                works = true;
                swap(nxt[i], nxt[j]);
                break;
            }
            if (not works) {
                cout << "0\n";
                return;
            }
            ans = (modval - ans) % modval;
        }

        ans = ans * nxt[i][i] % modval;

        ll curinv = pw(nxt[i][i], modval - 2);
        for (int j = i; j < n; j++) nxt[i][j] = nxt[i][j] * curinv % modval;

        for (int j = i + 1; j < n; j++) for (int l = n - 1; l >= i; l--) nxt[j][l] = (nxt[j][l] + modval - nxt[j][i] * nxt[i][l] % modval) % modval;
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
