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

const int L = 19;

ll pw[L];

int t, l;
ll n, ans;

ll gen(ll num, int len, int cnt) {
    ll res = 0;
    for (int i = 0; i < cnt; i++) {
        res *= pw[len];
        res += num;
    }
    return res;
}

void subcase() {
    pw[0] = 1;
    for (int i = 1; i < L; i++) pw[i] = 10 * pw[i - 1];

    cin >> n;
    
    l = 0;
    for (ll i = n; i > 0; i /= 10) l++;

    ans = gen(9, 1, l - 1);

    for (int i = 1; i < l; i++) {
        if (l % i) continue;
        ll val = n / pw[l - i], cur = gen(val, i, l / i);
        if (cur <= n) setmx(ans, cur);
        else setmx(ans, gen(val - 1, i, l / i));
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
