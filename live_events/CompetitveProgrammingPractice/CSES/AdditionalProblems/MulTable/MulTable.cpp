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

ll n, tar;

bool works(ll cur) {
    ll cnt = tar;
    for (int i = 1; i <= n; i++) {
        cnt -= min(cur / i, n);
        if (cnt <= 0) return true;
    }

    return false;
}

int main() {
    cin >> n;
    tar = n * n / 2 + 1;

    ll l = 1, r = n * n;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (works(mid)) r = mid;
        else l = mid + 1;
    }

    assert(l == r);
    cout << l << "\n";

	return 0;
}
