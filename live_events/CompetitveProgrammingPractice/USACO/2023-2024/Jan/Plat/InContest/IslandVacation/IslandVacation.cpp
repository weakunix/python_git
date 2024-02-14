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

int t, back[N];
ll prob[N];
bool vis[N];
vector<int> adj[N], child[N];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        a = a * a % modval;
        b >>= 1;
    }
    return res;
}

void dfs(int node, int parent) {
    vis[node] = true;
    for (int i : adj[node]) {
        if (i == parent) continue;
        if (vis[i]) {
            assert(back[node] == -1);
            back[node] = i;
        }
        else {
            child[node].pb(i);
            dfs(i, node);
        }
    }
    return;
}

void subcase() {
    clr(vis, false);
    clr(back, -1);
    fill(adj, adj + N, vector<int>());
    fill(child, child + N, vector<int>());

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> prob[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs1(0, -1);

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
