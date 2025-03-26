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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 1, N2 = 1000;

int t, m, n, l[N], r[N], u[N], d[N];
bool vis[N];
vector<int> adj[N2], radj[N2];
set<simps> miny[2 * N];

void solve1(int cur) {
    while (true) {
        auto it = miny[r[cur] - 1].begin();
        assert(it != miny[r[cur] - 1].end()); //shouldn't be empty since cur is less
        if (it->second == cur) it++;
        if (it == miny[r[cur] - 1].end() or it->first >= u[cur]) {
            cout << cur + 1 << " ";
            vis[cur] = true;
            for (int i = l[cur]; i < 2 * n; i++) miny[i].erase({d[cur], cur});
            return;
        }
        solve1(it->second);
    }

    assert(false);
    return;
}

void subcase() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> l[i] >> d[i] >> r[i] >> u[i];
    
    if (m == 1) {
        clr(vis, false);

        for (int i = 0; i < n; i++) for (int j = l[i]; j < 2 * n; j++) miny[j].insert({d[i], i});

        for (int i = 0; i < n; i++) if (not vis[i]) solve1(i);

        cout << "\n";
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            radj[i].clear();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j and u[i] > d[j] and r[i] > l[j]) {
                    adj[i].pb(j);
                    radj[j].pb(i);
                }
            }
        }
        for (int i = 0; i < n; i++) cout << (adj[i].empty() ? 1 : adj[i].back() < i);
        cout << "\n";
    }

    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> m;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
