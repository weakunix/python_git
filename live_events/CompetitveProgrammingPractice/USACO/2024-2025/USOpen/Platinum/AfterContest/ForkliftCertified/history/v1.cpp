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

const int N = 1000;

int t, m, n, l[N], r[N], u[N], d[N], rem[N];
vector<int> adj[N], radj[N];

void subcase() {

    cin >> n;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        radj[i].clear();
    }

    for (int i = 0; i < n; i++) cin >> l[i] >> d[i] >> r[i] >> u[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j and u[i] > d[j] and r[i] > l[j]) {
                adj[i].pb(j);
                radj[j].pb(i);
            }
        }
    }
    
    if (m == 1) {
        clr(rem, 0);
        queue<int> q;
        for (int i = 0; i < n; i++) if (adj[i].empty()) q.push(i);
        while (q.size()) {
            int cur = q.front();
            q.pop();
            cout << cur + 1 << " ";
            for (int i : radj[cur]) {
                rem[i]++;
                if (rem[i] == adj[i].size()) q.push(i);
            }
        }
        cout << "\n";
    }
    else {
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
