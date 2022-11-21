#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n;
    vector<int> indeg;
    vector<vector<int>> adj;
    vector<set<int>> ans;
    cin >> n;
    indeg.resize(n);
    adj.resize(n);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char cur;
            cin >> cur;
            if (cur == '0') continue;
            adj[i].push_back(j);
            indeg[j]++;
        }
    }
    for (int i = 0; i < n; i++) ans[i].insert(i + 1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i : adj[cur]) {
            for (int j : ans[cur]) ans[i].insert(j);
            indeg[i]--;
            if (indeg[i] == 0) q.push(i);
        }
    }
    for (set<int>& s : ans) {
        cout << s.size() << " ";
        for (int i : s) cout << i << " ";
        cout << "\n";
    }
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
