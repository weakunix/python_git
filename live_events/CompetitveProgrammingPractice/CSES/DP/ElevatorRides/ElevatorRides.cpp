#include <iostream>
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

int n, x;
vector<int> w;
vector<simps> dp;

int main() {
    cin >> n >> x;
    w.resize(n);
    dp.resize(1 << n, {1e9, 1e9}); dp[0] = {1, 0};
    for (int& i : w) cin >> i;
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) == 0) continue;
            int prv = i ^ (1 << j);
            if (dp[prv].second + w[j] <= x) dp[i] = min(make_pair(dp[prv].first, dp[prv].second + w[j]), dp[i]);
            else dp[i] = min(make_pair(dp[prv].first + 1, w[j]), dp[i]);
        }
    }
    cout << dp.back().first << "\n";
	return 0;
}
