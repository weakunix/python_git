#include <iostream>
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

const int N = 302, K = 7;

int n, k, vals[N], dp[1 << K][N][N], sz[1 << K], ans = -2e6;
simps rng[K];

void processinput() {
    vector<int> idx(k + 2);

    //vals
    vals[0] = 1e6;
    vals[n + 1] = 1e6;
    for (int i = 1; i <= n; i++) {
        cin >> vals[i];
        ans += vals[i];
    }

    //fixed
    idx[0] = 0;
    idx[k + 1] = n + 1;
    for (int i = 1; i <= k; i++) {
        cin >> idx[i];
        ans -= vals[idx[i]];
    }
    
    //find ranges
    int cnt = 0;
    for (int i = 0; i <= k; i++) {
        if (idx[i] + 1 == idx[i + 1]) {
            ans += max(vals[idx[i]], vals[idx[i + 1]]);
            continue;
        }
        rng[cnt] = {min(vals[idx[i]], vals[idx[i + 1]]), max(vals[idx[i]], vals[idx[i + 1]])};
        sz[1 << cnt] = idx[i + 1] - idx[i] - 1;
        cnt++;
    }

    //update n, k, vals
    for (int i : idx) vals[i] = 1e9;
    sort(vals, vals + n + 2);
    n -= k;
    k = cnt;

    return;
}

int main() {
    clr(sz, -1);

    cin >> n >> k;
    processinput();

    sz[0] = 0;
    for (int i = 1; i < (1 << k); i++) if (sz[i] == -1) sz[i] = sz[i & -i] + sz[i - (i & -i)];

    clr(dp[0], 0);
    for (int i = 1; i < (1 << k); i++) {
        for (int l = 0, r = sz[i] - 1; r < n; l++, r++) {
            dp[i][l][r] = 1e9;

            for (int j = 0; j < k; j++) {
                if (not ((1 << j) & i) or (sz[1 << j] == 1 and i != (1 << j))) continue;
                setmn(dp[i][l][r], dp[i ^ (1 << j)][l + 1][r - 1] + max(rng[j].first - vals[l], 0) + max(rng[j].second, vals[r]));
            }

            for (int j = (i - 1) & i; j > 0; j = (j - 1) & i) setmn(dp[i][l][r], dp[j][l][l + sz[j] - 1] + dp[i ^ j][l + sz[j]][r]);
        }

        for (int j = sz[i]; j < n; j++) {
            for (int l = 0, r = j; r < n; l++, r++) {
                dp[i][l][r] = min(dp[i][l + 1][r], dp[i][l][r - 1]);
            }
        }
    }

    cout << ans + dp[(1 << k) - 1][0][n - 1] << "\n";

	return 0;
}
