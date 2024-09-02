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

const int N = 2e5;

int t, n, ccid[N];
vector<int> adj[N];
vector<simps> ineq;
map<int, int> comp;

void dfs(int node, int curid) {
    ccid[node] = curid;
    for (int i : adj[node]) if (ccid[i] == -1) dfs(i, curid);
    return;
}

void subcase() {
    clr(ccid, -1);
    ineq.clear();
    comp.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, e;
        cin >> a >> b >> e;
        if (not comp.count(a)) {
            adj[comp.size()].clear();
            comp[a] = comp.size();
        }
        if (not comp.count(b)) {
            adj[comp.size()].clear();
            comp[b] = comp.size();
        }
        a = comp[a];
        b = comp[b];
        if (e == 0) ineq.pb({a, b});
        else {
            adj[a].pb(b);
            adj[b].pb(a);
        }
    }

    for (int i = 0; i < comp.size(); i++) if (ccid[i] == -1) dfs(i, i);

    for (simps& s : ineq) {
        if (ccid[s.first] == ccid[s.second]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
