#include <iostream>
#include <string>
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

int n, m;
bool seen = false;
string s, t;
vector<vector<int>> dp;

int main() {
    cin >> s >> t;
    n = s.size();
    m = t.size();
    dp.resize(n, vector<int>(m));
    seen = (s[0] == t[0]);
    dp[0][0] = not seen;
    for (int i = 1; i < n; i++) {
        if (s[i] == t[0]) seen = true;
        dp[i][0] = i + (not seen);
    }
    seen = (s[0] == t[0]);
    for (int i = 1; i < m; i++) {
        if (s[0] == t[i]) seen = true;
        dp[0][i] = i + (not seen);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (s[i] != t[j])});
    }
    cout << dp[n - 1][m - 1] << "\n";
	return 0;
}
