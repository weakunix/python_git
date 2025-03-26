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

const int N = 2e5;

int n, m;
ll ans = 0;
set<int> adj[N];

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u > v) swap(u, v);
        adj[u].insert(v);
    }
    for (int i = 0; i < n; i++) {
        if (adj[i].empty()) continue;
        ans += adj[i].size();
        int nxt = *adj[i].begin();
        adj[i].erase(nxt);
        if (adj[i].size() > adj[nxt].size()) swap(adj[i], adj[nxt]);
        for (int j : adj[i]) adj[nxt].insert(j);
    }
    cout << ans - m << "\n";
	return 0;
}
