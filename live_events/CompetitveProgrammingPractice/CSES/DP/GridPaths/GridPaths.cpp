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

int n;
vector<vector<int>> dp;
vector<vector<bool>> trap;

int main() {
    cin >> n;
    dp.resize(n + 1, vector<int>(n + 1));
    trap.resize(n + 1, vector<bool>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            trap[i][j] = (c == '*');
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (trap[i][j]) continue;
            dp[i][j] = (i == 1 and j == 1) ? 1 : (dp[i - 1][j] + dp[i][j - 1]) % modval;
        }
    }
    cout << dp[n][n] << "\n";
	return 0;
}
