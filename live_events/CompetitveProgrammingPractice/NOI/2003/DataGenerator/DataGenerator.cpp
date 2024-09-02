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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
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

const int N = 2e5;

int n;
ll ans = 0;
simps best[N][3];
vector<simps> adj[N];

void updbest(int node, int child, ll nw) {
    if (nw < best[node][0].first) return;
    best[node][0] = {nw, child};
    sort(best[node], best[node] + 3);
    return;
}

void dfs1(int node, int parent) {
    for (simps& s : adj[node]) {
        if (s.first == parent) continue;
        dfs1(s.first, node);
        updbest(node, s.first, best[s.first][2].first + s.second);
    }
    return;
}

void dfs2(int node, int parent, ll up, ll w) {
    if (parent != -1) {
        for (int i = 0; i < 3; i++) {
            if (best[parent][i].second == -1 or best[parent][i].second == node) continue;
            setmx(up, best[parent][i].first + w);
        }
    }
    ll a = -1, b = 0, c = up;
    if (b > c) swap(b, c);
    for (int i = 0; i < 3; i++) {
        if (best[node][i].second == -1) continue;
        setmx(a, best[node][i].first);
        if (a > b) swap(a, b);
        if (b > c) swap(b, c);
    }
    if (a != -1) setmx(ans, a + 2 * b + c);

    for (simps& s : adj[node]) if (s.first != parent) dfs2(s.first, node, max(up, 0ll) + s.second, s.second);

    return;
}

int main() {
    for (int i = 0; i < N; i++) for (int j = 0; j < 3; j++) best[i][j] = {0, -1};
    
    cin >> n >> n; n++;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    
    dfs1(0, -1);
    dfs2(0, -1, -1, -1);

    cout << ans << "\n";

	return 0;
}
