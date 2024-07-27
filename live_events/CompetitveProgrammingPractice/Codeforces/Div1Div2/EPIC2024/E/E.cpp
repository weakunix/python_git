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

const int N = 5000;

int t, n, lab[N], par[N], cost[N];
ll ans;
vector<int> adj[N];
pair<map<ll, ll>, int> margin[N];

void merge(int a, int b) {
    if (margin[a].first.size() < margin[b].first.size()) swap(margin[a], margin[b]);

    int dif = margin[b].second - margin[a].second;

    for (auto& u : margin[b].first) margin[a].first[u.first + dif] += u.second;

    return;
}

void dfs(int node) {
    margin[node] = {{}, 0};

    if (not adj[node].size()) {
        cost[node] = 0;
        return;
    }

    ll reqlab = 0;
    cost[node] = 1e9;
    for (int i : adj[node]) {
        dfs(i);
        reqlab += lab[i];
        setmn(cost[node], cost[i] + 1);
        merge(node, i);
    }

    margin[node].second++;

    if (lab[node] == reqlab) return;

    if (lab[node] < reqlab) {
        margin[node].first[-margin[node].second] += reqlab - lab[node];
        return;
    }

    while (margin[node].first.size()) {
        auto it = margin[node].first.begin();

        ll curcost = it->first + margin[node].second;
        if (curcost > cost[node]) {
            margin[node].first.erase(it);
            continue;
        }

        ll cnt = min(it->second, lab[node] - reqlab);
        ans += cnt * curcost;
        reqlab += cnt;
        it->second -= cnt;
        
        if (it->second == 0) margin[node].first.erase(it);
        
        if (lab[node] == reqlab) return;
    }

    ans += (lab[node] - reqlab) * cost[node];

    return;
}

void subcase() {
    ans = 0;
    par[0] = -1;
    adj[0].clear();

    cin >> n;
    for (int i = 0; i < n; i++) cin >> lab[i];
    for (int i = 1; i < n; i++) {
        adj[i].clear();

        cin >> par[i];
        par[i]--;
        adj[par[i]].pb(i);
    }

    dfs(0);

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
