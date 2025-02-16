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

int n;
bool arr[N];
ll dp1[N], dp2[N];
vector<int> adj[N];

void dfs(int node, int parent, int k) {
    ll sm1 = 0, sm2 = 0;
    for (int i : adj[node]) {
        if (i == parent) continue;
        dfs(i, node, k);
        sm1 += dp1[i];
        sm2 += dp2[i];
    }
    dp1[node] = sm2 + k + 1;
    dp2[node] = sm2 + 1;
    if (not arr[node]) {
        setmn(dp1[node], sm1);
        setmn(dp2[node], sm1);
    }
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        arr[i] = (c == '1');
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    for (int i = 1; i <= n; i++) {
        dfs(0, -1, i);
        cout << dp1[0] << "\n";
    }

	return 0;
}
