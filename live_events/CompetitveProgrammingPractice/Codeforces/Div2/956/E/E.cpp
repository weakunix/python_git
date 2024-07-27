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

const int modval = 1e9 + 7;

int t;

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        a = a * a % modval;
        b >>= 1;
    }
    return res;
}

void subcase() {
    int n, k;
    ll spec = 0, norm = 0;
    cin >> n >> k;
    n -= k;
    for (int i = 0; i < k; i++) {
        ll cur;
        cin >> cur;
        spec = (spec + cur) % modval;
    }
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        norm = (norm + cur) % modval;
    }

    ll a = (((n + 1) / 2) * pw(n, modval - 2) % modval * norm % modval + ((n + 2) / 2) * pw(n + 1, modval - 2) % modval * spec % modval) % modval;
    ll b = ((n / 2) * pw(n, modval - 2) % modval * norm % modval + ((n + 1) / 2) * pw(n + 1, modval - 2) % modval * spec % modval) % modval;
    cout << a << " " << b << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
