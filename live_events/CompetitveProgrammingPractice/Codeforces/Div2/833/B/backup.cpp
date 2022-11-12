#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

vector<vector<int>> dp(1e5 + 1, vector<int>(11, -1));

ll choose(int n, int m) {
    if (n == 1 or m % n == 0) return 1;
    if (dp[n][m] != -1) return dp[n][m];
    dp[n][m] = choose(n - 1, m - 1) + choose(n - 1, m);
    return dp[n][m];
}

void subcase() {
    int n, distinct = 0;
    ll ans = 1;
    string s;
    vector<int> count(10);
    cin >> n >> s;
    for (char c : s) count[c - '0']++;
    for (int i : count) distinct += (i > 0);
    for (int i = 0; i < 10; i++) {
        ll cur = 0;
        for (int j = 0; j <= distinct and j <= count[i]; j++) cur += choose(count[i], j);
        ans *= cur;
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
