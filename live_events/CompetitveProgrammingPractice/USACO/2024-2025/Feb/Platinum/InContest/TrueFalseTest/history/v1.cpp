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

const int N = 2005; //FIXME (small n only)

int n, q, a[N], b[N];
ll suma = 0, dp[N][N];
vector<simps> ord;

void solve(int k) {
    for (int i = 0; i <= n; i++) for (int j = 0; j <= k; j++) dp[i][j] = 1e10;
    dp[0][0] = 0;

    if (k == 0) {
        cout << suma << "\n";
        return;
    }
    
    ll ans = 1e18;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            setmn(dp[i + 1][j], dp[i][j] + a[ord[i].second]);
            setmn(dp[i + 1][j + 1], dp[i][j] + a[ord[i].second] + b[ord[i].second]);
        }
        setmn(ans, dp[i + 1][k]);
    }

    cout << suma - ans << "\n";
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        suma += a[i];
        ord.pb({a[i] + b[i], i});
    }
    sort(rall(ord));
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        solve(k);
    }
	return 0;
}
