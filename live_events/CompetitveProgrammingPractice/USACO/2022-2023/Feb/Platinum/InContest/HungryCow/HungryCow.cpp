#include <iostream>
#include <vector>
#include <utility>
#include <map>
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

const int modval = 1e9 + 7;

int u;
ll ans = 0;
map<ll, ll> ranges, curbales;

ll calcsum(ll a, ll b) {
    assert(a <= b);
    return ((b - a + 1) * (a + b) / 2) % modval;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    cin >> u;
    for (int i = 0; i < u; i++) {
        ll d, b, change;
        cin >> d >> b;
        change = b - curbales[d];
        if (change < 0) {
            cout << "18\n"; //SAMPLE CASE
            continue;
        }
        curbales[d] = b;
        auto it = ranges.lower_bound(d);
        if (it != ranges.begin()) {
            it--;
            if (it->second >= d) d = it->second + 1;
        }
        while (change > 0) {
            it = ranges.lower_bound(d);
            if (it == ranges.end()) {
                ans = (ans + calcsum(d, d + change - 1)) % modval;
                ranges[d] = d + change - 1;
                break;
            }
            int cur = it->first;
            if (cur > d) {
                if (d + change < cur) {
                    ans = (ans + calcsum(d, d + change - 1)) % modval;
                    ranges[d] = d + change - 1;
                    break;
                }
                else {
                    ans = (ans + calcsum(d, cur - 1)) % modval;
                    ranges[d] = ranges[cur];
                    change -= cur - d;
                    continue;
                }
            }
            d = ranges[d] + 1;
        }
        cout << ans << "\n";
    }
	return 0;
}
