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

const ll INF = 2e18;

int n, m, k;
vector<ll> ans;
vector<vector<ll>> adj;

int main() {
    cin >> n >> m >> k;
    ans.resize(n, INF); ans[0] = 0;
    adj.resize(n, vector<ll>(n, INF));
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a][b] = min(c, adj[a][b]);
    }
    while (k) {
        if (k & 1) {
            vector<ll> newans(n, INF);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) newans[i] = min(ans[j] + adj[j][i], newans[i]);
            }
            swap(ans, newans);
        }
        k >>= 1;
        vector<vector<ll>> newadj(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < n; l++) newadj[i][l] = min(adj[i][j] + adj[j][l], newadj[i][l]);
            }
        }
        swap(adj, newadj);
    }
    cout << (ans[n - 1] == INF ? -1 : ans[n - 1]) << "\n";
	return 0;
}
