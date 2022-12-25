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

int n, a, b, ans = 0;
vector<threesome> friends;
vector<vector<vector<int>>> dp;

int main() {
    cin >> n >> a >> b;
    friends.resize(n);
    dp.resize(n + 1, vector<vector<int>>(a + 1, vector<int>(b + 1)));
    for (int i = 0; i < n; i++) cin >> friends[i].first >> friends[i].sec >> friends[i].third;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= a; j++) {
            for (int k = 0; k <= b; k++) {
                dp[i + 1][j][k] = max(dp[i][j][k], dp[i + 1][j][k]);
                for (int cost = j + friends[i].sec, ice = k; cost >= j and ice <= b; cost--, ice += friends[i].third) {
                    if (cost > a) continue;
                    dp[i + 1][cost][ice] = max(dp[i][j][k] + friends[i].first, dp[i + 1][cost][ice]);
                }
            }
        }
    }
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) ans = max(dp[n][i][j], ans);
    }
    cout << ans << "\n";
	return 0;
}
