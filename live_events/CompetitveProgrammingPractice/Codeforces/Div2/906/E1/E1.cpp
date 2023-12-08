#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
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

int t;

void subcase() {
    int n, m, k, all0 = 0, ans = 0;
    vector<int> pfx, pfx1, pfx2;
    vector<simps> rng;
    map<int, vector<int>> overlapping;
    cin >> n >> m >> k;

    pfx.resize(n + 2);
    pfx1.resize(n + 2);
    pfx2.resize(n + 2);
    for (int i = 1; i <= n; i++) overlapping[i] = {};

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        pfx[l]++;
        pfx[r + 1]--;
        rng.push_back({l, r});

        vector<int> torem;
        for (auto it = overlapping.lower_bound(l); it != overlapping.end() and it->first <= r; it++) {
            if (it->second.size() == 2) torem.push_back(it->first);
            else it->second.push_back(i);
        }

        for (int j : torem) overlapping.erase(j);
    }

    for (int i = 1; i <= n; i++) {
        pfx[i] += pfx[i - 1];
        if (pfx[i] == 0) all0++;
        else if (pfx[i] == 1) pfx1[i]++;
        else if (pfx[i] == 2) pfx2[i]++;
    }

    for (int i = 1; i <= n; i++) {
        pfx1[i] += pfx1[i - 1];
        pfx2[i] += pfx2[i - 1];
    }

    int best1 = 0, best2 = 0;

    for (simps& s : rng) {
        best2 = max(pfx1[s.second] - pfx1[s.first - 1], best2);
        if (best1 < best2) swap(best1, best2);
    }

    ans = best1 + best2;

    for (auto& u : overlapping) {
        if (u.second.size() < 2) continue;
        simps a = rng[u.second[0]], b = rng[u.second[1]];
        if (a > b) swap(a, b);
        
        if (b.second <= a.second) ans = max(pfx1[a.second] - pfx1[a.first - 1] + pfx2[b.second] - pfx2[b.first - 1], ans);
        else ans = max(pfx1[b.second] - pfx1[a.first - 1] + pfx2[a.second] - pfx2[b.first - 1], ans);
    }

    cout << ans + all0 << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
