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

const int N = 3e5 + 1, L = 3;

int l, n;
ll c[N], dp[4][5001], nxt[4][5001];
bool s[N];

void opt(ll& cur, ll nw) {
    if (nw == -1) return;
    if (cur == -1) cur = nw;
    setmn(cur, nw);
    return;
}

void solve1() {
    for (int i = 0; i < n; i++) if (s[i]) c[i] = 0;
    sort(c, c + n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += c[i];
        cout << ans << "\n";
    }
    return;
}

int main() {
    clr(dp, -1);
    clr(nxt, -1);

    cin >> l >> n;
    for (int i = 0; i < n; i++) {
        char cur;
        cin >> cur;
        s[i] = (cur == 'M');
    }
    for (int i = 0; i < n; i++) cin >> c[i];

    if (l == 1) {
        solve1();
        return 0;
    }

    dp[l][0] = 0;
    nxt[l][0] = 0;
    for (int i = 0; i < n; i++) {
        clr(nxt, -1);

        for (int j = 0; j <= l; j++) {
            for (int k = 0; k <= n / l; k++) {
                if (dp[j][k] == -1) continue;

                opt(nxt[0][k], dp[j][k] + (s[i] ? 0 : c[i]));
                if (l == 1) opt(nxt[0][k + 1], dp[j][k] + (s[i] ? 0 : c[i]));
                opt(nxt[min(j + 1, l)][k], dp[j][k] + (s[i] ? c[i] : 0));
                if (j == l - 2) opt(nxt[min(j + 1, l)][k + 1], dp[j][k] + (s[i] ? c[i] : 0));
            }
        }

        memmove(dp, nxt, sizeof(nxt));
    }

    for (int i = 1; i <= n / l; i++) {
        ll ans = -1;
        for (int j = 0; j <= l; j++) opt(ans, dp[j][i]);
        cout << ans << "\n";
    }

	return 0;
}
