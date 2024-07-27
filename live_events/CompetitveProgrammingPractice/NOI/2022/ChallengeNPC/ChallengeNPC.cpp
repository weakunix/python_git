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

int t, k, n[2], rt[2], vals[2][N], sz[2][N];
vector<int> adj[2][N];
map<vector<int>, int> mp;

int getmp(vector<int>& v) {
    if (mp.count(v)) return mp[v];
    mp[v] = mp.size();
    return mp.size() - 1;
}

int dfs1(int tree, int node) {
    vector<int> cvals;
    sz[tree][node] = 1;
    for (int i : adj[tree][node]) {
        cvals.pb(dfs1(tree, i));
        sz[tree][node] += sz[tree][i];
    }
    sort(all(cvals));
    int cur = getmp(cvals);
    vals[tree][node] = cur;
    return cur;
}

int works(vector<int> node, int k) {
    if (vals[0][node[0]] == vals[1][node[1]]) return 0;
    vector<simps> cvals[2];
    for (int i = 0; i < 2; i++) {
        for (int j : adj[i][node[i]]) cvals[i].pb({vals[i][j], j});
        sort(all(cvals[i]));
    }

    vector<int> fail[2];

    while (cvals[0].size() and cvals[1].size()) {
        if (cvals[0].back().first == cvals[1].back().first) {
            cvals[0].bp();
            cvals[1].bp();
            continue;
        }
        if (cvals[0].back().first > cvals[1].back().first) {
            fail[0].pb(cvals[0].back().second);
            cvals[0].bp();
            continue;
        }
        fail[1].pb(cvals[1].back().second);
        cvals[1].bp();
    }

    for (int i = 0; i < 2; i++) for (simps s : cvals[i]) fail[i].pb(s.second);

    if (fail[0].size() > k or fail[0].size() < fail[1].size()) return 6;
    while (fail[1].size() < fail[0].size()) fail[1].pb(-1);
    sort(all(fail[1]));

    int best = 6;
    do {
        int cnt = 0;
        for (int i = 0; i < fail[0].size(); i++) {
            int a = fail[0][i], b = fail[1][i];
            if (b == -1) cnt += sz[0][a];
            else cnt += works({a, b}, k - cnt);
            if (cnt > k) break;
        }
        setmn(best, cnt);
    }
    while (next_permutation(all(fail[1])));

    return best;
}

void subcase() {
    for (int i = 0; i < 2; i++) {
        cin >> n[i];
        for (int j = 0; j < n[i]; j++) adj[i][j].clear();
        for (int j = 0; j < n[i]; j++) {
            int parent;
            cin >> parent;
            if (parent == -1) rt[i] = j;
            else adj[i][parent - 1].pb(j);
        }
        dfs1(i, rt[i]);
    }

    cout << (works({rt[0], rt[1]}, k) <= k ? "Yes\n" : "No\n");

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> t >> k;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
