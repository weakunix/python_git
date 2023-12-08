#include <iostream>
#include <cstring>
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

const int N = 2e5;

int n;
ll x, s[N], f[N], dp[N];

int main() {
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> f[i];
    
    for (int i = 0; i < n; i++) {
        dp[i] = x * s[i];
        for (int j = 0; j < i; j++) dp[i] = min(dp[j] + f[j] * s[i], dp[i]);
    }

    cout << dp[n - 1] << "\n";

	return 0;
}
