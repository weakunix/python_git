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
#include <cmath>
#include <numeric>
#include <cassert>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<double, double> simps;
typedef pair<double, simps> threesome;

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

const int N = 10;
const double eps = 1e-7;

int n, w, t, v;
threesome arr[N];

simps getrng(int idx, double tart) {
    double l = arr[idx].first, r = l + arr[idx].sec, s = arr[idx].third;
    if (s == 0) return {l, r};
    while (true) {
        if (s > 0) {
            double curt = (w - r) / s;
            if (curt < tart) {
                tart -= curt;
                l += (w - r);
                r = w;
                s = -s;
            }
            else {
                l += tart * s;
                r += tart * s;
                return {l, r};
            }
        }
        else {
            s = -s;
            double curt = l / s;
            if (curt < tart) {
                tart -= curt;
                r -= l;
                l = 0;
            }
            else {
                l -= tart * s;
                r -= tart * s;
                return {l, r};
            }
        }
    }
    assert(false);
    return {-1, -1};
}

double f(double x) {
    vector<simps> v(n);
    for (int i = 0; i < n; i++) v[i] = getrng(i, x);
    sort(all(v));

    double res = 0, cur = 0;
    for (simps& s : v) {
        if (cur < s.first) res += s.first - cur;
        setmx(cur, s.second);
    }

    res += w - cur;

    return res;
}

double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) / 6 * (f(l) + 4 * f(mid) + f(r));
}

double asimpson(double l, double r, double sm) {
    double mid = (l + r) / 2;
    double lsm = simpson(l, mid), rsm = simpson(mid, r);
    if (fabs(lsm + rsm - sm) < eps) return lsm + rsm;
    return asimpson(l, mid, lsm) + asimpson(mid, r, rsm);
}

int main() {
    cin >> n >> w >> t >> v;
    for (int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].sec >> arr[i].third;
    cout << fixed << setprecision(2) << asimpson(0, t, simpson(0, t)) * v << "\n";

	return 0;
}
