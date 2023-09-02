#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
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

const int modval = 1e9 + 7;

int n, m, k;
vector<ll> ans;
vector<map<int, ll>> adj;

int main() {
    cin >> n >> m >> k;
    ans.resize(n); ans[0] = 1;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a][b]++;
    }
    while (k) {
        if (k & 1) {
            vector<ll> newans(n);
            for (int i = 0; i < n; i++) {
                for (auto& j : adj[i]) newans[j.first] = (newans[j.first] + j.second * ans[i] % modval) % modval;
            }
            swap(ans, newans);
        }
        k >>= 1;
        vector<map<int, ll>> newadj(n);
        for (int i = 0; i < n; i++) {
            for (auto& j : adj[i]) {
                for (auto& k : adj[j.first]) newadj[i][k.first] = (newadj[i][k.first] + j.second * k.second % modval) % modval;
            }
        }
        swap(adj, newadj);
    }
    cout << ans.back() << "\n";
	return 0;
}
