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
vector<int> ans, to;
vector<bool> visited;

int main() {
    cin >> n;
    ans.resize(n, -1);
    to.resize(n);
    visited.resize(n);
    for (int& i : to) {
        cin >> i;
        i--;
    }
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            cout << ans[i] << " ";
            continue;
        }
        int node = i;
        vector<int> stck;
        while (not visited[node]) {
            stck.push_back(node);
            visited[node] = true;
            node = to[node];
        }
        if (ans[node] == -1) {
            vector<int> cycle;
            while (stck.back() != node) {
                cycle.push_back(stck.back());
                stck.pop_back();
            }
            cycle.push_back(node);
            stck.pop_back();
            for (int i : cycle) ans[i] = cycle.size();
        }
        while (not stck.empty()) {
            int cur = stck.back();
            stck.pop_back();
            ans[cur] = ans[to[cur]] + 1;
        }
        cout << ans[i] << " ";
    }
    cout << "\n";
	return 0;
}
