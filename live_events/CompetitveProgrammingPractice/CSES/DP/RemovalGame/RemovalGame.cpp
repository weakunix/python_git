#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
vector<vector<simps>> dp;

int main() {
    cin >> n;
    dp.resize(n, vector<simps>(n));
    for (int i = 0; i < n; i++) cin >> dp[i][i].first;
    for (int i = 1; i < n; i++) {
       for (int j = 0; j < n - i; j++) dp[j][j + i] = max(make_pair(dp[j][j].first + dp[j + 1][j + i].second, dp[j + 1][j + i].first), make_pair(dp[j + i][j + i].first + dp[j][j + i - 1].second, dp[j][j + i - 1].first));
    }
    cout << dp[0][n - 1].first << "\n";
	return 0;
}
