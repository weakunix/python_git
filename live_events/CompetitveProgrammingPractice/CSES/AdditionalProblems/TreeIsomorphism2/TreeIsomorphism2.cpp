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

int t, n, sz[2][N];
vector<int> adj[2][N], cent[2], vals[2][N];
map<vector<int>, int> mp = {{{}, 0}};

int dfs1(int tree, int node, int parent) {
    sz[tree][node] = 1;
    for (int i : adj[tree][node]) if (i != parent) sz[tree][node] += dfs1(tree, i, node);
    return sz[tree][node];
}

void getcent(int tree, int node, int parent) {
    for (int i : adj[tree][node]) {
        if (i == parent) continue;
        if (2 * sz[tree][i] > n) {
            getcent(tree, i, node);
            return;
        }
    }
    
    cent[tree].pb(node);

    simps nxt = {-1, -1};
    for (int i : adj[tree][node]) {
        if (i == parent) continue;
        setmx(nxt, {sz[tree][i], i});
    }

    if (2 * (n - nxt.first) <= n) cent[tree].pb(nxt.second);

    return;
}

int getmp(vector<int>& v) {
    if (mp.count(v)) return mp[v];
    mp[v] = mp.size();
    return mp.size() - 1;
}

int dfs2(int tree, int node, int parent, int depth) {
    vector<int> cur;
    for (int i : adj[tree][node]) if (i != parent) cur.pb(dfs2(tree, i, node, depth + 1));
    sort(all(cur));
    int curval = getmp(cur);
    vals[tree][depth].pb(curval);
    return curval;
}

bool works(vector<int> rt) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) vals[i][j].clear();
        dfs2(i, rt[i], -1, 0);
    }
    for (int i = 0; i < n; i++) {
        sort(all(vals[0][i]));
        sort(all(vals[1][i]));
        if (vals[0][i] != vals[1][i]) return false;
    }
    return true;
}

void subcase() {
    cin >> n;
    for (int i = 0; i < 2; i++) {
        cent[i].clear();
        for (int j = 0; j < n; j++) adj[i][j].clear();
        for (int j = 0; j < n - 1; j++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[i][a].pb(b);
            adj[i][b].pb(a);
        }
        dfs1(i, 0, -1);
        getcent(i, 0, -1);
    }

    for (int i : cent[0]) {
        if (works({i, cent[1][0]})) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
