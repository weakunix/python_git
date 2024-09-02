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

const int N = 1e6;

int n;
ll ans = 0;
vector<simps> adj[N];

int dfs(int node, int parent, ll w) {
    int sz = 1;
    for (simps& s : adj[node]) if (s.first != parent) sz += dfs(s.first, node, s.second);
    ans += w * abs(n - 2 * sz);
    return sz;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    
    dfs(0, -1, 0);

    cout << ans << "\n";

	return 0;
}
