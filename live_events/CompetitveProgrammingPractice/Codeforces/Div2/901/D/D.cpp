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
    int n, initmex = 0;
    vector<ll> dp;
    map<int, int> cnt;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cnt[cur]++;
    }
    while (cnt.count(initmex)) initmex++;
    dp.resize(initmex + 1);
    dp.back() = 0;
    for (int i = initmex - 1; i >= 0; i--) {
        int curcnt = cnt[i] - 1;
        dp[i] = 1e18;
        for (int j = i + 1; j <= initmex; j++) dp[i] = min(dp[j] + curcnt * j + i, dp[i]);
    }
    cout << dp[0] << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
