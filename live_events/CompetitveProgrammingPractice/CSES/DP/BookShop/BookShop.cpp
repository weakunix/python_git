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

int n, k, ans = 0;
vector<int> price, pages;
vector<vector<int>> dp;

int main() {
    cin >> n >> k;
    price.resize(n);
    pages.resize(n);
    dp.resize(n, vector<int>(k + 1));
    for (int i = 0; i < n; i++) cin >> price[i];
    for (int i = 0; i < n; i++) cin >> pages[i];
    if (price[0] <= k) dp[0][price[0]] = pages[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) dp[i][j] = max((j >= price[i]) ? dp[i - 1][j - price[i]] + pages[i] : 0, dp[i - 1][j]);
    }
    for (int i : dp[n - 1]) ans = max(i, ans);
    cout << ans << "\n";
	return 0;
}
