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

const int N = 1e5;

int t, n, m;
__int128 p[N], a[N], d[N], r[N], mn = 0;

void getdmg() {
    vector<ll> drop(n);
    for (int i = 0; i < n; i++) cin >> drop[i];

    multiset<ll> s;
    for (int i = 0; i < m; i++) {
        ll cur;
        cin >> cur;
        s.insert(cur);
    }

    for (int i = 0; i < n; i++) {
        auto it = s.ub(a[i]);
        if (it != s.begin()) it--;
        d[i] = *it;
        s.erase(it);
        s.insert(drop[i]);
        setmx(mn, (a[i] + d[i] - 1) / d[i]);
    }

    return;
}

__int128 gcd(__int128 a, __int128 b, __int128& x, __int128& y) {
    if (not b) {
        x = 1;
        y = 0;
        return a;
    }
    __int128 prvx, prvy, g = gcd(b, a % b, prvx, prvy);
    x = prvy;
    y = prvx - prvy * (a / b);
    return g;
}

void subcase() {
    mn = 0;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        a[i] = cur;
    }
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        p[i] = cur;
    }
    getdmg();

    for (int i = 0; i < n; i++) {
        __int128 x, y, g = gcd(d[i], p[i], x, y);

        if (a[i] % g) {
            cout << "-1\n";
            return;
        }

        p[i] /= g;
        a[i] /= g;
        r[i] = (x * a[i] % p[i] + p[i]) % p[i];
    }

    __int128 ans = 0, l = 1;
    for (int i = 0; i < n; i++) {
        __int128 x, y, g = gcd(l, p[i], x, y);

        if (r[i] % g != ans % g) {
            cout << "-1\n";
            return;
        }
        
        ans += x * l * (r[i] - ans) / g;
        l *= p[i] / g;
        ans = (ans % l + l) % l;
    }

    if (ans < mn) ans += (mn - ans + l - 1) / l * l;
    ll ansll = ans;
    cout << ansll << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
