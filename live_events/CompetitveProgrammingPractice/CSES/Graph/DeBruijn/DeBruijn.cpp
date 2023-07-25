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

int n, cur = 0;
vector<int> ans, stck = {0}, ansstck = {0};
vector<vector<simps>> adj;
vector<set<int>> visited;

int main() {
    cin >> n;
    if (n == 1) {
        cout << "01\n";
        return 0;
    }
    n--;
    adj.resize(1 << n);
    visited.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        int cur = i << 1;
        if (cur & (1 << n)) cur ^= 1 << n;
        for (int j = 0; j < 2; j++) adj[i].push_back({cur ^ j, j});
    }
    while (not stck.empty()) {
        if (visited[cur].size() == 2) {
            cur = stck.back();
            ans.push_back(ansstck.back());
            stck.pop_back();
            ansstck.pop_back();
        }
        else {
            stck.push_back(cur);
            for (simps s : adj[cur]) {
                if (visited[cur].count(s.first) > 0) continue;
                visited[cur].insert(s.first);
                cur = s.first;
                ansstck.push_back(s.second);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) cout << 0;
    for (int i = ans.size() - 2; i >= 0; i--) cout << ans[i];
    cout << "\n";
	return 0;
}
