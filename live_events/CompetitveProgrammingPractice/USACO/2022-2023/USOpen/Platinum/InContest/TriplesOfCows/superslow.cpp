#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
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
vector<unordered_set<int>> adj;

ll getans(int rnd) {
    ll ans = 0;
    for (int i = rnd; i < n; i++) {
        ll cur = adj[i].size();
        ans += cur * (cur - 1);
    }
    return ans;
}

int main() {
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for (int i = 0; i < n; i++) {
        cout << getans(i) << "\n";
        int sz = adj[i].size();
        vector<int> cur;
        for (int j : adj[i]) {
            cur.push_back(j);
            adj[j].erase(i);
        }
        for (int j = 0; j < sz; j++) {
            for (int k = j + 1; k < sz; k++) {
                adj[cur[j]].insert(cur[k]);
                adj[cur[k]].insert(cur[j]);
            }
        }
    }
	return 0;
}
