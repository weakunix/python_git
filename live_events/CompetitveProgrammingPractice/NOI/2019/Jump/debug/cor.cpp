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

const int N = 7e4;

int n, m, w, h, ans[N];
simps loc[N];
vector<vector<int>> edges[N];

int main() {
    clr(ans, -1);

    cin >> n >> m >> w >> h;
    for (int i = 0; i < n; i++) cin >> loc[i].first >> loc[i].second;
    for (int i = 0; i < m; i++) {
        int p, t, l, r, d, u;
        cin >> p >> t >> l >> r >> d >> u;
        p--;
        edges[p].pb({t, l, r, d, u});
    }

    ans[0] = 0;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for (vector<int> v : edges[0]) pq.push(v);

    while (pq.size()) {
        vector<int> cur = pq.top();
        pq.pop();

        for (int i = 1; i < n; i++) {
            if (ans[i] != -1) continue;
            if (loc[i].first < cur[1] or loc[i].first > cur[2]) continue;
            if (loc[i].second < cur[3] or loc[i].second > cur[4]) continue;
            ans[i] = cur[0];
            for (vector<int> v : edges[i]) {
                v[0] += cur[0];
                pq.push(v);
            }
        }
    }

    for (int i = 1; i < n; i++) cout << ans[i] << "\n";

	return 0;
}
