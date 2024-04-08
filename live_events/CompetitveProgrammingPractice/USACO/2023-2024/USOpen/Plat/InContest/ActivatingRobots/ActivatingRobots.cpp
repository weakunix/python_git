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

const int N = 100, R = 10;

ll l, r, n, k, arr[N], dp[1 << R][N], ans = 1e18;

void special() {
    for (int i = 0; i < n; i++) {
        ll cur, t;
        cin >> cur;
        t = min(cur, l - cur);
        ll modt = (l + cur - l / 2) % l * k;
        if (t <= modt) setmn(ans, modt);
        else setmn(ans, modt + l * k);
    }
    cout << ans << "\n";
}

int main() {
    for (int i = 0; i < (1 << R); i++) fill(dp[i], dp[i] + N, 1e18);

    cin >> l >> r >> n >> k;

    if (r == 2) {
        special();
        return 0;
    }

    for (int i = 0; i < n; i++) cin >> arr[i];

    for (ll i = 0; i < n; i++) dp[1][i] = min(arr[i], l - arr[i]);

    for (ll i = 1; i < (1 << r); i++) {
        if (not (i & 1)) continue;
        for (ll j = 1; j < r; j++) {
            if (i & (1 << j)) continue;

            for (ll b = 0; b < n; b++) {
                for (ll a = 0; a < n; a++) {
                    ll curt = dp[i][a];
                    if (arr[b] >= arr[a]) curt += min(arr[b] - arr[a], l + arr[a] - arr[b]);
                    else curt += min(arr[a] - arr[b], l + arr[b] - arr[a]);

                    ll modt = (l + arr[b] - l / r * j) % l * k, div = (curt / (l * k)) * l * k;

                    if (curt - div <= modt) curt = div + modt;
                    else curt = div + (l * k) + modt;
                    
                    setmn(dp[i ^ (1 << j)][b], curt);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) setmn(ans, dp[(1 << r) - 1][i]);
    cout << ans << "\n";

	return 0;
}
