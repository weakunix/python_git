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

ll cross(simps a, simps b) {
    return a.first * b.second - a.second * b.first;
}

void subcase() {
    ll a, b, ans = 0;
    cin >> a >> b;

    simps prv = {1, 0};
    for (int i = 1; i <= b; i++) {
        ll x = a * i / b + 1;
        if (x + i > a + b) continue;
        if (cross(prv, {x, i}) > 0) {
            ans++;
            prv = {x, i};
        }
    }

    prv = {1, 0};
    for (int i = 1; i <= a; i++) {
        ll x = b * i / a + (b * i % a != 0);
        if (x == 0) continue;
        if (cross(prv, {x, i}) >= 0) {
            ans++;
            prv = {x, i};
        }
    }

    cout << ans << "\n";

	return;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);

	cin >> t;
	for (int i = 0; i < t; i++) subcase();

	return 0;
}
