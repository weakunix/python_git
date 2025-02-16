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

const int N = 1e5;

int n, w[N], par[N];
ll add[N], sub[N];
vector<int> adj[N], ord;

void dfs(int node, int parent) {
    par[node] = parent;
    for (int i : adj[node]) if (i != parent) dfs(i, node);
    ord.pb(node);
    return;
}

int main() {
    clr(add, 0);
    clr(sub, 0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 0; i < n; i++) cin >> w[i];

    dfs(0, -1);

    for (int i : ord) {
        for (int j : adj[i]) {
            if (j == par[i]) continue;
            setmx(add[i], add[j]);
            setmx(sub[i], sub[j]);
        }
        
        ll cur = w[i] + add[i] - sub[i];
        if (cur > 0) sub[i] += cur;
        else if (cur < 0) add[i] -= cur;
    }

    cout << add[0] + sub[0] << "\n";

	return 0;
}
