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

const int N = 3001;

int n;
ll a[N][N], cost[N][N], dp[N];

int main() {
    clr(a, 0);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i][i];
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) a[i][j] = a[i][j - 1] + a[j][j];

    for (int j = 0; j < n; j++) {
        for (int i = j; i >= 0; i--) {
            cost[i][j] = min(2 * a[i + 1][j] + cost[i + 1][j], 3 * (j - i) * a[i][i] + a[i + 1][j] + cost[i + 1][j]);
        }
    }

    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1e18;
        for (int j = i; j < n; j++) {
            setmn(dp[i], cost[i][j] + (4 * j - 4 * i + 2) * a[j + 1][n - 1] + dp[j + 1]);
        }
    }

    cout << dp[0] << "\n";

	return 0;
}
