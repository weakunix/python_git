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

int n, tar;
vector<int> coins, dp;

int main() {
    cin >> n >> tar;
    coins.resize(n);
    dp.resize(tar + 1, 1e9);
    dp[0] = 0;
    for (int i = 0; i < n; i++) cin >> coins[i];
    sort(all(coins));
    for (int i = 1; i <= tar; i++) {
        for (int j : coins) {
            if (i - j < 0) break;
            dp[i] = min(dp[i - j] + 1, dp[i]);
        }
    }
    cout << (dp[tar] == 1e9 ? -1 : dp[tar]) << "\n";
	return 0;
}
