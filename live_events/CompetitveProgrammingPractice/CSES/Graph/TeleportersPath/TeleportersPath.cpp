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

int n, m, cur;
vector<int> indeg, stck = {0}, ans;
vector<set<int>> adj;

int main() {
    cin >> n >> m;
    cur = n - 1;
    indeg.resize(n);
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        indeg[b]++;
    }
    adj[n - 1].insert(0);
    indeg[0]++;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() != indeg[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    while (not stck.empty()) {
        if (adj[cur].empty()) {
            ans.push_back(cur);
            cur = stck.back();
            stck.pop_back();
        }
        else {
            int nxt = *adj[cur].begin();
            stck.push_back(cur);
            adj[cur].erase(nxt);
            cur = nxt;
        }
    }
    if (ans.size() != m + 2) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = m; i >= 0; i--) cout << ans[i] + 1 << " ";
    cout << "\n";
	return 0;
}
