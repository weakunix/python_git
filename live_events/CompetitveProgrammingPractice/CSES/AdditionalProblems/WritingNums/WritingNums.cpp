#include <iostream>
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

ll n, pw[19];

bool works(ll cur) {
    ll cnt = n;
    for (int i = 0; i < 18; i++) {
        int d = cur / pw[i] % 10;
        if (d == 0) cnt -= cur / pw[i + 1] * pw[i];
        else if (d == 1) cnt -= cur / pw[i + 1] * pw[i] + cur % pw[i] + 1;
        else cnt -= (cur / pw[i + 1] + 1) * pw[i];
        if (cnt < 0) return false;
    }
    return true;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < 19; i++) pw[i] = 10 * pw[i - 1];

    cin >> n;

    ll l = 0, r = 1e18 - 1;
    while (l < r) {
        ll mid = l + (r - l + 1) / 2;
        if (works(mid)) l = mid;
        else r = mid - 1;
    }

    assert(l == r);
    cout << l << "\n";

	return 0;
}
