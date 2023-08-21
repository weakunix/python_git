#include <iostream>
#include <cstring>
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
vector<int> ans;
vector<vector<int>> adj;
vector<set<int>> sub;

void dfs(int node, int par) {
    for (int i : adj[node]) {
        if (i == par) continue;
        dfs(i, node);
        if (sub[i].size() > sub[node].size()) swap(sub[i], sub[node]);
        for (int j : sub[i]) sub[node].insert(j);
    }
    ans[node] = sub[node].size();
    return;
}

int main() {
    cin >> n;
    ans.resize(n);
    sub.resize(n);
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        sub[i].insert(cur);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
