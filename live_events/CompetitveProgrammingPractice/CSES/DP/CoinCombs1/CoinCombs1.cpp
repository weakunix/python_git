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

const int modval = 1e9 + 7;

int n, k;
vector<int> coins, dp;

int main() {
    cin >> n >> k;
    coins.resize(n);
    dp.resize(k + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) cin >> coins[i];
    sort(all(coins));
    for (int i = 1; i <= k; i++) {
        for (int j : coins) {
            if (i - j < 0) continue;
            dp[i] = (dp[i] + dp[i - j]) % modval;
        }
    }
    cout << dp[k] << "\n";
	return 0;
}
