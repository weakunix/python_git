#include <iostream>
#include <cstdio>
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
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 1e5;

int t, n;
vector<int> adj[2][N];
map<vector<int>, int> mp = {{{}, 0}};

int getmp(vector<int>& cvals) {
    if (mp.count(cvals)) return mp[cvals];
    mp[cvals] = mp.size();
    return mp.size() - 1;
}

int dfs(int tree, int node, int parent, int depth) {
    vector<int> cvals;
    for (int i : adj[tree][node]) {
        if (i == parent) continue;
        cvals.pb(dfs(tree, i, node, depth + 1));
    }
    sort(all(cvals));
    return getmp(cvals);
}

void subcase() {
    mp.clear();

    cin >> n;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) adj[i][j].clear();
        for (int j = 0; j < n - 1; j++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[i][a].pb(b);
            adj[i][b].pb(a);
        }
    }

    cout << (dfs(0, 0, -1, 0) == dfs(1, 0, -1, 0) ? "YES\n" : "NO\n");
    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
