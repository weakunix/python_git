#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 1e5, modval = 1e9 + 7;

int n, k, m, mns[N], arr[N];
ll ans = 1;
vector<simps> rng;
multiset<int> mx;

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll calc(ll val, int len) {
    val = 1e9 - val;
    if (len <= k) return (pw(val + 1, len) + modval - pw(val, len)) % modval;
    ll rem = pw(val, k);
    vector<ll> dp(len + 1);
    dp[0] = 1;
    for (int i = 1; i <= k - 1; i++) dp[i] = dp[i - 1] * (val + 1) % modval;
    dp[k] = (pw(val + 1, k) + modval - rem) % modval;
    for (int i = k + 1; i <= len; i++) dp[i] = ((val + 1) * dp[i - 1] % modval + modval - rem * dp[i - k - 1] % modval) % modval;
    return dp[len];
}

int main() {
    freopen("tracking2.in", "r", stdin);
    freopen("tracking2.out", "w", stdout);

    memset(arr, 0, sizeof(arr));

    cin >> n >> k;
    for (int i = 0; i < n - k + 1; i++) cin >> mns[i];

    if (k == 1) {
        cout << "1\n";
        return 0;
    }

    for (int i = 0; i < n - k; i++) {
        if (mns[i] < mns[i + 1]) arr[i] = mns[i];
        else if (mns[i] > mns[i + 1]) arr[i + k] = mns[i + 1];
    }
    
    for (int i = 0; i < n; i++) {
        if (i < n - k + 1) mx.insert(mns[i]);
        if (i >= k) mx.erase(mx.find(mns[i - k]));
        if (not arr[i]) arr[i] = *mx.rbegin();

        if (rng.size() and rng.back().first == arr[i]) rng.back().second++;
        else rng.push_back({arr[i], 1});
    }

    m = rng.size();

    if (m == 1) {
        cout << calc(rng[0].first, rng[0].second) << "\n";
        return 0;
    }

    for (int i = 1; i < m - 1; i++) {
        if (rng[i].first > rng[i - 1].first and rng[i].first > rng[i + 1].first) ans = ans * calc(rng[i].first, rng[i].second) % modval;
        else {
            int len = rng[i].second - 1;
            if (rng[i].first < rng[i - 1].first and rng[i].first < rng[i + 1].first) len--;
            if (len < k) ans = ans * pw(1e9 - rng[i].first + 1, len) % modval;
            else ans = ans * calc(rng[i].first, len) % modval;

        }
    }
    if (rng[0].first > rng[1].first) ans = ans * calc(rng[0].first, rng[0].second) % modval;
    else {
        int len = rng[0].second - 1;
        if (len < k) ans = ans * pw(1e9 - rng[0].first + 1, len) % modval;
        else ans = ans * calc(rng[0].first, len) % modval;
    }
    if (rng[m - 1].first > rng[m - 2].first) ans = ans * calc(rng[m - 1].first, rng[m - 1].second) % modval;
    else {
        int len = rng[m - 1].second - 1;
        if (len < k) ans = ans * pw(1e9 - rng[m - 1].first + 1, len) % modval;
        else ans = ans * calc(rng[m - 1].first, len) % modval;
    }

    cout << ans << "\n";
	return 0;
}
