#include <iostream>
#include <cstdio>
#include <string>
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

const int N = 1e5;

int t;

bool dfs1(int node, vector<simps> (&adj)[N], int (&vals)[N], int curval) {
    vals[node] = curval;
    for (simps s : adj[node]) {
        if (vals[s.first] == 2 and not dfs1(s.first, adj, vals, curval * s.second)) return false;
        else if (vals[s.first] != curval * s.second) return false;
    }
    return true;
}

void dfs2(int node, vector<simps> (&adj)[N], int (&vals)[N]) {
    vals[node] = 0;
    for (simps s : adj[node]) if (vals[s.first]) dfs2(s.first, adj, vals);
    return;
}

void subcase() {
    int n, m, vals[N], ans = 0;
    simps arr[N]; //{0, x}: pos[i] = x, {1, x}: pos[i] = pos[x], {-1, x}: pos[i] = NOT pos[x]
    vector<simps> adj[N], revadj[N];

    fill(vals, vals + N, 2);

    cin >> n >> m;

    for (int i = 0; i < n; i++) arr[i] = {1, i};
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == '-') {
            int a, b;
            cin >> a >> b;
            a--; b--;
            if (arr[b].first == 0) arr[a] = {0, -arr[b].second};
            else arr[a] = {-arr[b].first, arr[b].second};
        }
        else if (c == '+') {
            int a, b;
            cin >> a >> b;
            a--; b--;
            arr[a] = arr[b];
        }
        else {
            int a;
            cin >> a;
            a--;
            arr[a].first = 0;
            if (c == 'T') arr[a].second = 1;
            else if (c == 'F') arr[a].second = -1;
            else arr[a].second = 0;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (arr[i].first == 0) {
            vals[i] = arr[i].second;
            q.push(i);
        }
        else if (arr[i].second == i) {
            if (arr[i].first == 1) vals[i] = 1;
            else vals[i] = 0;
            q.push(i);
        }
        else {
            adj[arr[i].second].push_back({i, arr[i].first});
            adj[i].push_back({arr[i].second, arr[i].first});
        }
    }

    while (not q.empty()) {
        int node = q.front();
        q.pop();
        for (simps s : adj[node]) {
            if (vals[s.first] != 2) continue;
            vals[s.first] = s.second * vals[node];
            q.push(s.first);
        }
    }

    for (int i = 0; i < n; i++) {
        if (vals[i] == 2 and not dfs1(i, adj, vals, 1)) dfs2(i, adj, vals);
        //dfs1(i, revadj, vals, vals[i]);
        ans += (vals[i] == 0);
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    //freopen("tribool.in", "r", stdin);
    //freopen("tribool.out", "w", stdout);

	cin >> t >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
