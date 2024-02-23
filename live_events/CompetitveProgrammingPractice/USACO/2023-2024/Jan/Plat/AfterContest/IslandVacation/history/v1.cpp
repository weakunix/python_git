#include <iostream>
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

const int N = 1e4, modval = 1e9 + 7;

int t, n, m, deg[N];
ll p[N], ans[N];
vector<int> adj[N];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

void dfs(int node, int parent) {
    if (node == 0) ans[0] = 1;
    else ans[node] = ans[parent] * (modval + 1 - p[parent]) % modval * pw(deg[parent], modval - 2) % modval;
    for (int i : adj[node]) if (i != parent) dfs(i, node);
    if (adj[node].size() > 1 or not node) ans[node] = ans[node] * p[node] % modval;
    return;
}

void subcase() {
    memset(deg, -1, sizeof(deg));
    deg[0] = 0;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        adj[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        deg[a]++;
        deg[b]++;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) cout << ans[i] << (i == n - 1 ? "\n" : " ");
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
