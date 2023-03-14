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
    //ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);
    cin >> u;
    for (int i = 0; i < u; i++) {
        ll d, b, change;
        cin >> d >> b;
        change = b - curbales[d];
        curbales[d] = b;
        while (change > 0) {
            auto it = ranges.lower_bound(d);
            ll cur = it->first;
            if (cur > d) {
                if (it != ranges.begin()) {
                    it--;
                    if (it->second >= d) {
                        d = cur;
                        continue;
                    }
                }
                if (d + b < cur) {
                    ranges[d] = d + b - 1;
                    ans = (ans + calcsum(d, d + b - 1)) % modval;
                    change = 0;
                }
                else {
                    ans = (ans + calcsum(d, cur - 1)) % modval;
                    change -= cur - d;
                    ranges[d] = ranges[cur];
                    ranges.erase(cur);
                }
            }
            else {
                it++;
                if (it == ranges.end()) {
                    ans = (ans + calcsum(range[cur] + 1, range[cur] + change)) % modval;
                    range[cur] += change;
                    change = 0;
                    continue;
                }
            }
        }
        cout << ans << "\n";
    }
	return 0;
}
