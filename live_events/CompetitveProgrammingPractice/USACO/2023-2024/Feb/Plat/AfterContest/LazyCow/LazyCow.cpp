#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <complex>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef complex<ll> pt;
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
#define x real()
#define y imag()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

void cinpt(pt& p) {
	ll curx, cury;
	cin >> curx >> cury;
	p = {curx, cury};
	return;
}

ll cross(pt a, pt b) {
	return (conj(a) * b).y;
}

bool cmp(pt a, pt b) {
    return (a.x == b.x ? a.y < b.y : a.x < b.x);
}

const int modval = 1e9 + 7;

int n;
ll ans = 0;
set<pt, decltype(cmp)*> hull(cmp);

ll pw(ll a, ll b) {
    if (b < 0) return 0;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

pt getprv(pt cur) {
    auto it = hull.lb(cur);
    if (it == hull.begin()) return {-1, -1};
    it--;
    return *it;
}

pt getnxt(pt cur) {
    auto it = hull.ub(cur);
    if (it == hull.end()) return {-1, -1};
    return *it;
}

ll getans(pt l, pt r) {
    int m = r.x - l.x;
    ll b = r.y - l.y;
    return ((m - b % m) * pw(3, b / m - 1) % modval + b % m * pw(3, b / m) % modval) % modval;
}

int main() {
    hull.insert({0, 0});

    cin >> n;
    for (int i = 0; i < n; i++) {
        if (i) cout << ans << "\n";

        pt cur;
        cinpt(cur);

        pt l = getprv(cur), r = getnxt(cur);
        assert(l.x != -1); //ASSERT

        if (r.x == -1) {
            if (cur.y <= l.y) continue;
            while (hull.size() >= 2) {
                r = getprv(cur);
                l = getprv(r);
                if (cross(r - l, cur - l) < 0) break;
                ans = (ans + modval - getans(l, r)) % modval;
                hull.erase(r);
            }
            l = getprv(cur);
            ans = (ans + getans(l, cur)) % modval;
            hull.insert(cur);
            continue;
        }

        if (cross(r - l, cur - l) <= 0) continue;

        ans = (ans + modval - getans(l, r)) % modval;

        r = getprv(cur);
        l = getprv(r);
        while (l.x != -1 and cross(r - l, cur - l) >= 0) {
            ans = (ans + modval - getans(l, r)) % modval;
            hull.erase(r);
            r = getprv(cur);
            l = getprv(r);
        }
        l = getprv(cur);
        ans = (ans + getans(l, cur)) % modval;

        l = getnxt(cur);
        r = getnxt(l);
        while (r.x != -1 and cross(r - cur, l - cur) < 0) {
            ans = (ans + modval - getans(l, r)) % modval;
            hull.erase(l);
            l = getnxt(cur);
            r = getnxt(l);
        }
        r = getnxt(cur);
        if (r.y > cur.y) ans = (ans + getans(cur, r)) % modval;
        else hull.erase(l);

        hull.insert(cur);
    }

    cout << ans << "\n";

	return 0;
}
