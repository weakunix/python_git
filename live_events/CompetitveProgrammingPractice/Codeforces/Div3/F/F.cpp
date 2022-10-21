#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void Subcase() {
    int n, left, right;
    ll ans = 0;
    vector<int> p, loc;
    cin >> n;
    p.resize(n);
    loc.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        loc[p[i]] = i;
    }
    left = loc[0];
    right = loc[0];
    for (int i = 0; i < (n + 1) / 2; i++) {
        left = min(loc[i], left);
        right = max(loc[i], right);
        if (2 * i + 1 <= n and right - left + 1 <= 2 * i + 1) ans += min(n - 1 - 2 * i, left) - max(right - 2 * i, 0) + 1;
        if (2 * i + 2 <= n and right - left + 1 <= 2 * i + 2) ans += min(n - 2 - 2 * i, left) - max(right - 2 * i - 1, 0) + 1;
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
