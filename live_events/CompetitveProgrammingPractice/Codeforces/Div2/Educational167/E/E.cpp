#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5 + 1, K = 11, modval = 998244353;

int n, k;
ll dp[N][K], dpsm[N][K];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    clr(dp, 0);
    clr(dpsm, 0);

    cin >> n >> k;

    dp[0][0] = 1;
    dpsm[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = (dpsm[i - 1][max(j - 1, 0)] + modval - (i > 2 and i < n ? dp[i - 2][max(j - 1, 0)] : 0)) % modval;
            dpsm[i][j] = (dpsm[i - 1][j] + dp[i][j]) % modval;
        }
    }

    cout << dp[n][k] << "\n";

	return 0;
}
