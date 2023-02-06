#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
ll ans = 0;
vector<int> par, dep, sub;
vector<threesome> best1, best2;
vector<vector<int>> adj;
set<simps> ord;

int dfs(int node, int depth) {
    dep[node] = depth;
    ord.insert({depth, node});
    best1[node] = {0, {0, -1}};
    best2[node] = {0, {0, -1}};
    for (int i : adj[node]) {
        sub[node] += dfs(i, depth + 1);
        best1[node] = max(make_pair(best1[i].first + 1, make_pair(sub[i], i)), best1[node]);
    }
    for (int i : adj[node]) {
        if (i == best1[node].third) best2[node] = max(make_pair(best2[i].first, make_pair(sub[i], i)), best2[node]);
        else best2[node] = max(make_pair(best1[i].first + 1, make_pair(sub[i], i)), best2[node]);
    }
    return sub[node];
}

int main() {
    cin >> n;
    par.resize(n, -1);
    dep.resize(n);
    sub.resize(n, 1);
    best1.resize(n);
    best2.resize(n);
    adj.resize(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        par[i] = p;
        adj[p].push_back(i);
    }
    dfs(0, 0);
    while (not ord.empty()) {
        int a = ord.begin()->second, b = a;
        ord.erase(ord.begin());
        ans += 2 * sub[a];
        a = best1[a].third;
        b = best2[b].third;
        while (a != -1) {
            ord.erase({dep[a], a});
            a = best1[a].third;
        }
        while (b != -1) {
            ord.erase({dep[b], b});
            b = best2[b].third;
        }
    }
    cout << ans << "\n";
	return 0;
}
