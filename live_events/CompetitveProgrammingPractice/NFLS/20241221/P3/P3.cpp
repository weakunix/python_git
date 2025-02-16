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

int n, c, d[N], v[N];
ll cw[N], ccw[N], ans = 0;
multiset<ll> cwms, ccwms;

ll getbig(multiset<ll>& ms) {
    auto it = ms.end();
    it--;
    return *it;
}

int main() {
    cin >> n >> c;
    for (int i = 0; i < n; i++) cin >> d[i] >> v[i];

    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += v[i];
        cw[i] = cnt - d[i];
        cwms.insert(cw[i]);
        setmx(ans, cw[i]);
    }

    cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        cnt += v[i];
        ccw[i] = cnt - (c - d[i]);
        ccwms.insert(ccw[i]);
        setmx(ans, ccw[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        ccwms.erase(ccwms.find(ccw[i]));
        setmx(ans, cw[i] + getbig(ccwms) - d[i]);
    }

    for (int i = n - 1; i > 0; i--) {
        cwms.erase(cwms.find(cw[i]));
        setmx(ans, ccw[i] + getbig(cwms) - (c - d[i]));
    }

    cout << ans << "\n";

	return 0;
}
