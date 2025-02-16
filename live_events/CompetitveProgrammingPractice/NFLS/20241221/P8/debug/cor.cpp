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

const int N = 200;

int n, d[N], c[N];
vector<int> adj[N], ord;
ll ans = 1e18;

int main() {

    cin >> n;
    for (int i = 0; i < n; i++) cin >> d[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    for (int i = 0; i < n; i++) ord.pb(i);
    
    do {
        int curd[N];
        ll cur = 0;

        memcpy(curd, d, sizeof(curd));

        for (int i : ord) {
            cur += curd[i];
            for (int j : adj[i]) curd[j] = max(curd[j] - c[i], 0);
        }

        setmn(ans, cur);
    }
    while (next_permutation(all(ord)));

    cout << ans << "\n";

	return 0;
}
