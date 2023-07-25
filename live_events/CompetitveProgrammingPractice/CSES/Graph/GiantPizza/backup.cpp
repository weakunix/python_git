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

int n, m;
vector<int> ans, changed;
vector<bool> like, dislike;
vector<vector<int>> adj;

bool dfs(int node) {
    int cur = node % m;
    bool selected = node < m;
    if ((ans[cur] == 0 and selected) or (ans[cur] == 1 and not selected)) return false;
    if (ans[cur] != -1) return true;
    ans[cur] = selected;
    changed.push_back(cur);
    for (int i : adj[node]) {
        if (not dfs(i)) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> m;
    ans.resize(m, -1);
    like.resize(m);
    dislike.resize(m);
    adj.resize(2 * m);
    for (int i = 0; i < n; i++) {
        int a, b;
        char ta, tb;
        cin >> ta >> a >> tb >> b;
        a--; b--;
        if (ta == '-') {
            dislike[a] = true;
            a += m;
        }
        else like[a] = true;
        if (tb == '-') {
            dislike[b] = true;
            b += m;
        }
        else like[b] = true;
        adj[(a + m) % (2 * m)].push_back(b);
        adj[(b + m) % (2 * m)].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) continue;
        changed.clear();
        if (like[i] xor dislike[i]) {
            if (like[i]) dfs(i);
            else dfs(i + m);
            continue;
        }
        if (dfs(i)) continue;
        while (not changed.empty()) {
            ans[changed.back()] = -1;
            changed.pop_back();
        }
        if (dfs(i + m)) continue;
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i : ans) cout << (i ? '+' : '-') << " ";
    cout << "\n";
	return 0;
}
