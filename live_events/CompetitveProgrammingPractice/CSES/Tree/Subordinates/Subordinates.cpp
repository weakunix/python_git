#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
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

int dfs(int node) {
    for (int i : adj[node]) ans[node] += dfs(i);
    return ans[node] + 1;
}

int main() {
    cin >> n;
    ans.resize(n);
    adj.resize(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[p - 1].push_back(i);
    }
    dfs(0);
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
