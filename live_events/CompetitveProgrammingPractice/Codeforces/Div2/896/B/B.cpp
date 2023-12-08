#include <iostream>
#include <string>
#include <cstring>
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

const int N = 2e5;
ll MX = 1e18;

int t;

void subcase() {
    int n, k, a, b;
    ll x[N], y[N], dista = MX, distb = MX;

    cin >> n >> k >> a >> b;
    a--; b--;

    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i < k; i++) {
        dista = min(abs(x[a] - x[i]) + abs(y[a] - y[i]), dista);
        distb = min(abs(x[b] - x[i]) + abs(y[b] - y[i]), distb);
    }
    ll ans = min(dista + distb, abs(x[a] - x[b]) + abs(y[a] - y[b]));
    assert(ans >= 0);
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
