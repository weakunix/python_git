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

int n, sm;
vector<int> dp;

int main() {
    cin >> n;
    sm = n * (n + 1) / 2;
    if (sm % 2 > 0) {
        cout << "0\n";
        return 0;
    }
    dp.resize(sm + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = sm; j >= i; j--) dp[j] = (dp[j] + dp[j - i]) % modval;
    }
    cout << (dp[sm / 2] % 2 == 0 ? dp[sm / 2] / 2 : (dp[sm / 2] + modval) / 2) << "\n";
	return 0;
}
