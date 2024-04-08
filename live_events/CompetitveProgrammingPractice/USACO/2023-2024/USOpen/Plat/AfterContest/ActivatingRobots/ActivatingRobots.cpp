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

const int N = 1e5, R = 20;

ll l, r, n, k, arr[N], dist[R], dp[1 << R][R], ans = 1e18;

int main() {
    clr(dp, -1);

    cin >> l >> r >> n >> k;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);

    dist[0] = 0;
    for (int i = 1; i < r; i++) {
        ll t = k - 1, mv = i * l / r - k + 1;
        if (mv) {
            mv = max(mv - 2, (ll) 0);
            t++;
            int cur = mv / (k + 1);
            mv -= cur * (k + 1);
            t += cur * k;
            if (mv) t += mv;
        }
        dist[i] = t;

        if (k > 1) {
            t = k - 1;
            mv = (r - i) * l / r - k + 1;
            if (mv) {
                t++;
                int cur = mv / (k - 1);
                mv -= cur * (k - 1);
                t += cur * k;
                if (mv) t += mv;
                else t--;
            }
            setmn(dist[i], t);
        }
    }

    dp[1][0] = 0;
    for (int i = 1; i < (1 << r); i++) {
        if (not (i & 1)) continue;
        for (int j = 0; j < r; j++) {
            if (not (i & 1 << j) or dp[i][j] == -1) continue;

            int a = j * l / r;

            if (i != 1 or j != 0) {
                ll t = dp[i][j], mv = ((arr[(lb(arr, arr + n, (a + t / k + (t % k != 0)) % l) - arr) % n] - t / k - a) % l + l) % l;
                if (mv) {
                    if (t % k) {
                        t = (t / k + 1) * k;
                        mv--;
                    }
                    t += mv * k;
                }
                dp[i][j] = t;
            }

            for (int o = 0; o < r; o++) {
                if (i & 1 << o) continue;

                ll cur = dp[i][j] + dist[(j + r - o) % r];
                if (dp[i ^ 1 << o][o] == -1) dp[i ^ 1 << o][o] = cur;
                else setmn(dp[i ^ 1 << o][o], cur);

            }
        }
    }

    for (int i = 1; i < r; i++) setmn(ans, dp[(1 << r) - 1][i]);

    cout << ans << "\n";

	return 0;
}
