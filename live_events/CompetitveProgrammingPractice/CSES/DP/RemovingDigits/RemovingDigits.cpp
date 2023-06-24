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

int n;
vector<int> dp;

int main() {
    cin >> n;
    dp.resize(n + 1, 1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int cur = i;
        for (; cur > 0; cur /= 10) dp[i] = min(dp[i - cur % 10] + 1, dp[i]);
    }
    cout << dp[n] << "\n";
	return 0;
}
