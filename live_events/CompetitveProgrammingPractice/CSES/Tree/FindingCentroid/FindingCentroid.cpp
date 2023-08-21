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

int n, ans = 0;
vector<int> par, sub;
vector<vector<int>> adj;

int dfs(int node) {
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        sub[node] += dfs(i);
    }
    return sub[node];
}

int main() {
    cin >> n;
    par.resize(n, -1);
    sub.resize(n, 1);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    while (true) {
        int nxt = -1;
        for (int i : adj[ans]) {
            if (i != par[ans] and sub[i] > n / 2) {
                nxt = i;
                break;
            }
        }
        if (nxt == -1) {
            cout << ans + 1 << "\n";
            return 0;
        }
        ans = nxt;
    }
	return 0;
}
