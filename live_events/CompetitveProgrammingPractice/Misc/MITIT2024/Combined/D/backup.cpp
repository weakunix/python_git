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
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5;

int t, x;

void dfs(int node, vector<vector<int>>& adj, vector<int>& ord) {
    for (int i : adj[node]) dfs(i, adj, ord);
    ord.pb(node);
    return;
}

void subcase() {
    int n;
    vector<int> par, ord;
    vector<vector<int>> adj;
    vector<vector<ll>> dp;

    cin >> n;
    n++;
    par.resize(n, -1);
    adj.resize(n);
    dp.resize(n, vector<ll>(4, -1e9));

    for (int i = 1; i < n; i++) {
        cin >> par[i];
        par[i]--;
        adj[par[i]].pb(i);
    }

    dfs(0, adj, ord);

    for (int i : ord) {
        if (adj[node].empty()) {
            dp[i][0] = 0;
            dp[i][1] = 0;
            continue;
        }

        dp[i][0] = 0;
        for (int j : adj[node]) {
            ll cur = dp[j][0];
            cur = setmx(cur, max(dp[j][1], dp[j][2]) + 1);
            dp[i][0] += cur;
        }
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> x;
    assert(x == 0); //TODO ONLY SUBTASK 1
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
