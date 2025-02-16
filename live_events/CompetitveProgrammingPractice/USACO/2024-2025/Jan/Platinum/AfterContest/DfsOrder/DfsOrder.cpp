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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 751;

int n, a[N][N], dp[N][N], rem[N][N];
bool alr[N][N];

int main() {
    clr(alr, false);

    cin >> n;
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            cin >> a[i][j];
            if (a[i][j] < 0) {
                alr[i][j] = true;
                a[i][j] *= -1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        rem[i][n] = 0;
        for (int j = n - 1; j >= i; j--) rem[i][j] = rem[i][j + 1] + (alr[i][j] ? a[i][j] : 0);
    }

    for (int i = 0; i < n; i++) dp[i][i] = rem[i][i + 1];

    for (int i = 1; i < n; i++) {
        for (int l = 0, r = l + i; r < n; l++, r++) {
            dp[l][r] = 1e9;
            for (int m = l; m < r; m++) {
                int cur = dp[l][m] + dp[m + 1][r] + (alr[l][m + 1] ? 0 : a[l][m + 1]) + rem[l][r + 1] - rem[l][m + 1];
                //for (int j = l; j <= m; j++) cur += rem[j][r + 1] - rem[j][m + 1];
                setmn(dp[l][r], cur);
            }
        }
    }

    cout << dp[0][n - 1] << "\n";

	return 0;
}
