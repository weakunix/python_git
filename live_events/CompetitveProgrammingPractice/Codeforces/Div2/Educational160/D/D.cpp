#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 3e5, modval = 998244353;

int t, arr[N];

ll solve(vector<int>& v) {
    int n = v.size();
    if (not n) return 1;

    ll lsm = 1;
    vector<ll> dp(n), dpsm(n);
    vector<simps> stck;
    dp[0] = 1;
    dpsm[0] = 1;
    stck.push_back({v[0], 0});

    for (int i = 1; i < v.size(); i++) {
        while (stck.size() and stck.back().first > v[i]) {
            lsm = (lsm + modval - dp[stck.back().second]) % modval;
            stck.pop_back();
        }
        if (stck.empty()) dp[i] = (dpsm[i - 1] + 1) % modval;
        else dp[i] = (dpsm[i - 1] + modval - dpsm[stck.back().second] + lsm) % modval;
        dpsm[i] = (dpsm[i - 1] + dp[i]) % modval;
        lsm = (lsm + dp[i]) % modval;
        stck.push_back({v[i], i});
    }

    return dpsm.back() + 1;
}

void subcase() {
    int n;
    simps mn = {2e9, -1};
    vector<int> l, r;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mn = min(make_pair(arr[i], i), mn);
    }
    for (int i = 0; i < mn.second; i++) l.push_back(arr[i]);
    for (int i = n - 1; i > mn.second; i--) r.push_back(arr[i]);
    cout << solve(l) * solve(r) % modval << "\n";

	return;
}

int main() {
   	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
