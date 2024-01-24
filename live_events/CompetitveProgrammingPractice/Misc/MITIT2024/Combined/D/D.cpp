#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t, x;

void subcase() {
    int n, ans = 0;
    vector<bool> col, vis;
    vector<vector<int>> adj;

    cin >> n;
    n++;
    col.resize(n);
    vis.resize(n);
    adj.resize(n);

    for (int i = 1; i < n; i++) {
        int node;
        cin >> node;
        node--;
        adj[node].pb(i);
        adj[i].pb(node);
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            q.push(i);
            vis[i] = true;
        }
    }

    while (q.size()) {
        int node = q.front();
        q.pop();

        if (adj[node].size() == 1) {
            col[node] = true;
            q.push(adj[node][0]);
            vis[adj[node][0]] = true;
            continue;
        }

        int red = 0, green = 0;
        bool done = true;
        for (int i : adj[node]) {
            if (not vis[i]) {
                q.push(i);
                vis[i] = true;
                done = false;
                continue;
            }
            if (col[i]) green++;
            else red++;
        }

        if (green) col[node] = false;
        else col[node] = (red == 1 or (done and red == 2));
    }

    for (int i = 0; i < n; i++) ans += col[i];
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> x;
    assert(x == 0); //TODO ONLY SUBTASK 1
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
