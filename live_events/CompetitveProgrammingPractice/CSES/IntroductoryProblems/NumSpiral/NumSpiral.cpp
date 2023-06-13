#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int t;

void subcase() {
    ll y, x, mx, cur;
    cin >> y >> x;
    mx = max(x, y);
    cur = (mx * mx + (mx - 1) * (mx - 1) + 1) / 2;
    if (mx % 2 == 0) {
        if (x == mx) cout << cur - (mx - y) << "\n";
        else cout << cur + (mx - x) << "\n";
    }
    else {
        if (x == mx) cout << cur + (mx - y) << "\n";
        else cout << cur - (mx - x) << "\n";
    }
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
