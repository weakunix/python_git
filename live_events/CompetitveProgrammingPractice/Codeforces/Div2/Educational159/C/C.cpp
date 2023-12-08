#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2e5;

int t;
ll arr[N];

void subcase() {
    ll n, g = -1, mx = -2e9;
    ll ans = 0;
    set<ll> s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
        mx = max(arr[i], mx);

        if (i == 0) continue;
        ll cur = abs(arr[i] - arr[i - 1]);
        if (g == -1) g = cur;
        else g = gcd(cur, g);
    }

    if (n == 1) {
        cout << "1\n";
        return;
    }

    for (int i = 0; i < n; i++) ans += (mx - arr[i]) / g;

    ll cur = mx;
    while (s.count(cur)) cur -= g;
    ans += (mx - cur) / g;

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
