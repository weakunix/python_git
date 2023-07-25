#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int modval = 1e9 + 7;

int n, m;
vector<int> indeg, ans;
vector<vector<int>> adj;
queue<int> q;

int main() {
    cin >> n >> m;
    indeg.resize(n);
    ans.resize(n); ans[0] = 1;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        indeg[b]++;
    }
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    while (not q.empty()) {
        int node = q.front();
        q.pop();
        for (int i : adj[node]) {
            indeg[i]--;
            if (indeg[i] == 0) q.push(i);
            ans[i] = (ans[i] + ans[node]) % modval;
        }
    }
    cout << ans[n - 1] << "\n";
	return 0;
}
