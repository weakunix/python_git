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

const int N = 1e5;

struct Frac {
    __int128 num, den;

    Frac() : num(0), den(1) {}

    Frac(__int128 _num, __int128 _den) : num(_num), den(_den) {
        if (den < 0) {
            num *= -1;
            den *= -1;
        }
        return;
    }

    bool isint() {
        return num % den == 0;
    }

    __int128 floor() {
        return num / den;
    }

    ~Frac() {}
};

bool operator<(Frac a, Frac b) {
    return a.num * b.den < b.num * a.den;
}

bool operator>(Frac a, Frac b) {
    return a.num * b.den > b.num * a.den;
}

int t, n;
__int128 p[N], need[N];

bool works(__int128 k) {
    Frac lo(0, 1), hi(k, 1);

    if (n % 2 == 1 and k * (n / 2) < p[n / 2]) return false;

    for (int i = n - 1; 2 * i + 1 - n > 0; i--) setmx(lo, Frac(p[i] - k * (n - 1 - i), 2 * i + 1 - n));
    for (int i = 0; 2 * i + 1 - n < 0; i++) setmn(hi, Frac(p[i] - k * (n - 1 - i), 2 * i + 1 - n));

    if (lo > hi) return false;

    if (lo.isint() or lo.floor() < hi.floor()) return true;

    __int128 a = lo.floor(), b = k - 1 - a, curlb = 0;
    vector<pair<__int128, int>> curub;
    
    for (int i = 0; i < n; i++) {
        need[i] = p[i] - a * i - b * (n - 1 - i);
        curub.pb({i - need[i], i});
    }
    sort(rall(curub));

    while (curub.size() and curub.back().first < curlb) {
        setmx(curlb, curub.back().second + need[curub.back().second]);
        curub.bp();
    }

    return (curlb < n);
}

void subcase() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        p[i] = cur;
    }

    ll lo = 0, hi = 2e18;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (works(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
