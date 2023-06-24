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
    for (int i : coins) {
        for (int j = i; j <= k; j++) dp[j] = (dp[j] + dp[j - i]) % modval;
    }
    cout << dp[k] << "\n";
	return 0;
}
