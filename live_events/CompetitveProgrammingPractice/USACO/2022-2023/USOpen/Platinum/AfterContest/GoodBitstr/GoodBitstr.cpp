#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t;

void subcase() {
    ll a, b, lo, hi, ans = 0;
    bool works = false;
    cin >> a >> b;
    lo = b;
    hi = a;

    while (hi != 0) {
        if (lo > hi) {
            ll cur = (lo - 1) / hi;
            lo -= cur * hi;
            ans += cur + (works ? cur : 0);
        }
        else {
            ans += hi / lo;
            hi %= lo;
            works = true;
        }
    }

    cout << ans + 2 * (lo - 1) << "\n";

	return;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);

	cin >> t;
	for (int i = 0; i < t; i++) subcase();

	return 0;
}
