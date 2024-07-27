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

const int N = 1e5;

int t, n, m, par[N], ht[N];
vector<int> adj[N];

void dfs(int node, int parent, int height) {
    par[node] = parent;
    ht[node] = height;

    for (int i : adj[node]) if (i != parent) dfs(i, node, height + 1);
    
    return;
}

bool dfsfind(int node, int tar) {
    if (node == tar) return true;
    for (int i : adj[node]) if (i != par[node] and dfsfind(i, tar)) return true;
    return false;
}

int main() {
	cin >> t >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs(0, -1, 0);

	return 0;
}
