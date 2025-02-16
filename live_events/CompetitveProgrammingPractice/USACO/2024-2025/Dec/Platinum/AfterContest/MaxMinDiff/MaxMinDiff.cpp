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

const int N = 2005, modval = 1e9 + 7;
ll fact[N], invfact[N];

int t, n, k, p[N];
ll ans;

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll choose(int a, int b) {
    if (a < 0 or b < 0 or b > a) return 0;
    return fact[a] * invfact[b] % modval * invfact[a - b] % modval;
}

void flipp() {
    for (int i = 0; i < n; i++) if (p[i] != -1) p[i] = n - 1 - p[i];
    return;
}

ll even(int l, int r, int big) { //(2m) m 0 [+ - ... - +]
    int prv = n / 2;
    ll res = 1;
    vector<simps> lims;
    
    for (int i = l; i <= r; i++) {
        if (p[i] == -1) continue;
        if (p[i] == n / 2) return 0;
        if (i % 2 == l % 2) { //+
            if (p[i] < n / 2) return 0;
            if (p[i] > big) return 0;
            lims.pb({p[i], i});
        }
        else { //-
            if (p[i] > n / 2) return 0;
            if (p[i] >= big - n / 2) return 0;
            lims.pb({p[i] + n / 2, i});
        }
    }

    if (lims.empty()) return pw(2, (r - l) / 2);

    sort(all(lims));

    for (int i = 0; i < lims.size() - 1; i++) {
        if (lims[i].first == lims[i + 1].first) {
            if (lims[i].second + 1 != lims[i + 1].second) return 0;
            if (lims[i].second < l or lims[i + 1].second > r) return 0;
            if (lims[i].second % 2 == l % 2) { //->
                int cnt = lims[i].first - prv - 1, need = (lims[i].second - l) / 2;
                res = res * choose(cnt, need) % modval;
                prv = lims[i].first;
                l = lims[i].second + 2;
                r -= 2 * (cnt - need);
            }
            else { //<-
                int cnt = lims[i].first - prv - 1, need = (r - lims[i + 1].second) / 2;
                res = res * choose(cnt, need) % modval;
                prv = lims[i].first;
                l += 2 * (cnt - need);
                r = lims[i + 1].second - 2;
            }
            i++;
            if (i == lims.size() - 1) return res * pw(2, (r - l) / 2) % modval;
            continue;
        }
        if (lims[i].second < l or lims[i].second > r) return 0;
        if (lims[i + 1].second > lims[i].second) { //->
            int cnt = lims[i].first - prv - 1, need = (lims[i].second - l) / 2;
            res = res * choose(cnt, need) % modval;
            prv = lims[i].first;
            l += 2 * need + 2;
            r -= 2 * (cnt - need);
        }
        else { //<-
            int cnt = lims[i].first - prv - 1, need = (r - lims[i].second) / 2;
            res = res * choose(cnt, need) % modval;
            prv = lims[i].first;
            l += 2 * (cnt - need);
            r -= 2 * need + 2;
        }
    }

    if (lims.back().second < l or lims.back().second > r) return 0;
    if (lims.back().first == big) return res * choose((r - l) / 2, (lims.back().second - l) / 2) % modval;
    res = res * (choose(lims.back().first - prv - 1, (lims.back().second - l) / 2) + choose(lims.back().first - prv - 1, (r - lims.back().second) / 2)) % modval;
    return res * pw(2, big - lims.back().first - 1) % modval;
}

ll odd(int l, int r, int idx) { //[+ - ... -] 2m m 0 [+ - ... -]
    int prv = n / 2;
    ll res = 1;
    vector<simps> lims;

    for (int i = l; i < idx - 1; i++) {
        if (p[i] == -1) continue;
        if (p[i] == n / 2) return 0;
        if (i % 2 == l % 2) { //+
            if (p[i] < n / 2) return 0;
            lims.pb({p[i], i});
        }
        else { //-
            if (p[i] > n / 2) return 0;
            lims.pb({p[i] + n / 2, i});
        }
    }
    for (int i = r; i < n; i++) {
        if (p[i] == -1) continue;
        if (p[i] == n / 2) return 0;
        if (i % 2 == r % 2) { //+
            if (p[i] < n / 2) return 0;
            lims.pb({p[i], i});
        }
        else { //-
            if (p[i] > n / 2) return 0;
            lims.pb({p[i] + n / 2, i});
        }
    }

    sort(all(lims));
    
    for (int i = 0; i < lims.size(); i++) {
        if (i > 0 and lims[i].first == lims[i - 1].first) {
            if (lims[i - 1].second + 1 != lims[i].second) return 0;
            if (lims[i].second < idx and lims[i].second % 2 == l % 2) return 0;
            if (lims[i].second > idx and lims[i].second % 2 == r % 2) return 0;
            continue;
        }
        if (lims[i].second < l or (lims[i].second > idx and lims[i].second < r)) return 0;
        if (lims[i].second < idx) { //left
            int cnt = lims[i].first - prv - 1, need = (lims[i].second - l) / 2;
            res = res * choose(cnt, need) % modval;
            prv = lims[i].first;
            l += 2 * need + 2;
            r += 2 * (cnt - need);
        }
        else { //right
            int cnt = lims[i].first - prv - 1, need = (lims[i].second - r) / 2;
            res = res * choose(cnt, need) % modval;
            prv = lims[i].first;
            l += 2 * (cnt - need);
            r += 2 * need + 2;
        }
    }

    return res * choose((idx - 2 - l + 1) / 2 + (n - 1 - r + 1) / 2, (idx - 2 - l + 1) / 2) % modval;
}

ll solve() {
    ll res = 0;

    if (p[0] == n / 2 or p[0] == -1) {
        for (int i = 0; i < 2; i++) {
            if (p[1] == 0 or p[1] == -1) res = (res + even(2, n - 1, n - 1)) % modval;
            flipp();
        }
    }

    for (int i = 1; i < n - 1; i++) {
        if (p[i] != n / 2 and p[i] != -1) continue;
        if (p[i - 1] != n - 1 and p[i - 1] != -1) continue;
        if (p[i + 1] != 0 and p[i + 1] != -1) continue;

        if (i % 2 == 1) res = (res + odd(0, i + 2, i)) % modval;
        else {
            ll a = even(i + 2, n - 1, n - 1 - i / 2);
            flipp();
            ll b = even(0, i - 2, n / 2 + i / 2);
            flipp();
            res = (res + a * b % modval) % modval;
        }
    }

    return res;
}

void subcase() {
    ans = 0;
    clr(p, -1);

    cin >> k;

    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        p[a] = b;
    }

    if (n % 2 == 0) {
        ans = 2;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                int cur = n / 2 - 1 - j / 2 + (j % 2 == 1 ? n / 2 : 0);
                if (p[j] == cur or p[j] == -1) continue;
                ans--;
                break;
            }
            reverse(p, p + n);
        }

        cout << ans << "\n";

        return;
    }


    ans = (ans + solve()) % modval;
    reverse(p, p + n);
    ans = (ans + solve()) % modval;

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = pw(fact[N - 1], modval - 2);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

	cin >> t >> n;
	for (int i = 0; i < t; i++) subcase();

	return 0;
}
