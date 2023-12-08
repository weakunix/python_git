#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
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

const int N = 2e5 + 1, K = 11;

int t, n, m, k, dp[K][4 * N];

void setseg(int sid, int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        dp[sid][node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(sid, 2 * node, l, mid, idx, val);
    setseg(sid, 2 * node + 1, mid + 1, r, idx, val);
    dp[sid][node] = max(dp[sid][2 * node], dp[sid][2 * node + 1]);
    return;
}

int getseg(int sid, int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return dp[sid][node];
    int mid = l + (r - l) / 2;
    return max(getseg(sid, 2 * node, l, mid, a, b), getseg(sid, 2 * node + 1, mid + 1, r, a, b));
}

void subcase() {
    int ans = 0;
    map<int, vector<int>> olap;

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) olap[i] = {};
    for (int i = 0; i < m; i++) {
        int a, b;
        vector<int> rem;
        cin >> a >> b;
        
        for (auto it = olap.lower_bound(a); it != olap.upper_bound(b); it++) {
            if (it->second.size() >= k) rem.push_back(it->first);
            else it->second.push_back(a);
        }

        for (int j : rem) olap.erase(j);
    }

    for (int i = 0; i <= k; i++) setseg(i, 1, 0, n, 0, 0);

    for (int l = 1; l <= n; l++) {
        if (not olap.count(l)) {
            for (int i = 0; i <= k; i++) setseg(i, 1, 0, n, l, 0);
            continue;
        }
        
        vector<int>& arr = olap[l];
        sort(all(arr));

        for (int i = 0; i < arr.size(); i++) setseg(i, 1, 0, n, l, 0);

        for (int i = arr.size(); i <= k; i++) {
            int cur = (i == 0 ? 0 : getseg(i - 1, 1, 0, n, l, l));
            cur = max(getseg(i - arr.size(), 1, 0, n, 0, l - 1) + 1, cur);
            for (int j = 0; j < arr.size(); j++) cur = max(getseg(i - arr.size() + 1 + j, 1, 0, n, arr[j], l - 1) + 1, cur);
            ans = max(cur, ans);
            setseg(i, 1, 0, n, l, cur);
        }
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
